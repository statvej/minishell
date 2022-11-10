/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:38:44 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/10 17:02:12 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char **find_path(char **envp)
{
	int		i;
	char	**path;

	i = 0;
	while (ft_strncmp("PATH", envp[i], 4))
		i++;
	path = ft_split(envp[i] + 5, ':');
	return (path);
}

char	*find_command(char **path, char *command)
{
	int		i;
	char	*result;
	char	*temp;
	i = 0;
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		result = ft_strjoin(temp, command);
		if (!access(result, F_OK))
		{
			free(temp);
			return (result);
		}
		free(result);
		i++;
	}
	return (0);
}

void process(t_cmd_group *cmd_grp, char **envp)
{
	fprintf(stderr, "%s\n %s", );
	cmd_grp->command = find_command(cmd_grp->pos_paths, cmd_grp->args[0]);
	if (!cmd_grp->command)
	{
		perror("command doesn't exist");
	}
	else
		execve(cmd_grp->command, cmd_grp->args, envp);
}

void arr_execute(t_cmd_group *cmd_grp, char **envp)
{
	if (pipe(cmd_grp->pipes) < 0)
		perror("ERROR with pipes");
	cmd_grp->child = fork();
	if (cmd_grp->child == -1)
		perror("ERROR with forks");
	if (cmd_grp->child == 0)
	{
		close(cmd_grp->pipes[0]);
		while(cmd_grp->out)
		{
			dup2(cmd_grp->out->val, STDOUT_FILENO);
			cmd_grp->out = cmd_grp->out->next;
		}
		dup2(cmd_grp->pipes[1], STDOUT_FILENO);
		close(cmd_grp->pipes[1]);
		process(cmd_grp, envp);
	}
	else
	{
		close(cmd_grp->pipes[1]);
		while(cmd_grp->in)
		{
			dup2(cmd_grp->in->val, STDIN_FILENO);
			cmd_grp->in = cmd_grp->in->next;
		}
		dup2(cmd_grp->pipes[0], STDIN_FILENO);
		close(cmd_grp->pipes[0]);
		waitpid(cmd_grp->child, NULL, 0);
	}
	
}

int post_pipe_exec(t_cmd_group *cmd_group, char **envp)
{
	cmd_group->child = fork();
	if (cmd_group->child == -1)
	{
		perror("ERROR wit forks");
		return -1;
	}
	if (cmd_group->child == 0)
	{
		while(cmd_group->out)
		{
			if (dup2(cmd_group->out->val, STDOUT_FILENO) == -1)
				perror("ERROR wit pipes");
			cmd_group->out = cmd_group->out->next;
		}
		process(cmd_group, envp);
	}
	else
	{
		while(cmd_group->in)
		{
			dup2(cmd_group->in->val, STDIN_FILENO);
			cmd_group->in = cmd_group->in->next;
		}
		waitpid(cmd_group->child, NULL, 0);
	}
	return SUCCESS;
}

int execution(t_pipe_group *pipe_grp, char **envp)
{
	t_pipe_group *temp;
	char **path;

	temp = pipe_grp;
	path = find_path(envp);
	// mx_print_strarr();
	if (temp->next)
	{	
		// fprintf(stderr, "III");
		while(temp->next)
		{
			temp->cmd_group->pos_paths = path;
			arr_execute(temp->cmd_group, envp);
			temp = temp->next;
		}
		temp = temp->next;
		fprintf(stderr, "\nIII\n");
	}
	temp->cmd_group->pos_paths = path;
	if(post_pipe_exec(temp->cmd_group, envp) == ERROR)
		return ERROR;
	return SUCCESS;
}