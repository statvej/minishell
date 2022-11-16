/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:38:44 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/16 17:35:09 by fstaryk          ###   ########.fr       */
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

void process(t_cmd_group *cmd_grp, char **envp, char **pp)
{
	cmd_grp->command = find_command(pp, cmd_grp->args[0]);
	
	if (!cmd_grp->command)
	{
		perror("command doesn't exist");
	}
	else
		execve(cmd_grp->command, cmd_grp->args, envp);
}

void create_pipes(t_log_group *log_grp)
{
	t_pipe_group *temp;

	temp = log_grp->pipe_group;
	if (temp->next)
	{
		while(temp->next)
		{
			pipe(temp->cmd_group->pipes);
			temp = temp->next;
		}		
	}
}

void execute(t_pipe_group *pipe_grp, t_data *data)
{
	t_cmd_group *temp_cmd;
	int status;
	
	temp_cmd = pipe_grp->cmd_group;
	temp_cmd->child = fork();
	if(temp_cmd->child == 0)
	{
		if(pipe_grp->next)
		{
			if ((dup2(temp_cmd->pipes[1], STDOUT_FILENO)) == -1)
				perror("ERR_OUTFILE");
		}
		if(pipe_grp->prev)
		{
			if ((dup2(pipe_grp->prev->cmd_group->pipes[0], STDIN_FILENO)) == -1)
				perror("ERR_OUTFILE");
			
		}
		while(temp_cmd->in)
		{
			dup2(temp_cmd->in->val, STDIN_FILENO);
			temp_cmd->in = temp_cmd->in->next;
		}
		while(temp_cmd->out)
		{
			dup2(temp_cmd->out->val, STDOUT_FILENO);
			temp_cmd->out = temp_cmd->out->next;
		}
		process(temp_cmd, data->envp, data->pos_paths);
	}
	else
	{
		if(pipe_grp->prev && pipe_grp->prev->cmd_group->pipes[0] > 2)
			close(pipe_grp->prev->cmd_group->pipes[0]);
		if(temp_cmd->pipes[1] > 2)
			close(temp_cmd->pipes[1]);
		waitpid(temp_cmd->child, &status, 0);
		//in case of success
		if(status != 256)
			data->last_log_ret = 1;
		//in case of failer
		else
			data->last_log_ret = 0;
	}
}

void close_pipes(t_log_group *log_grp)
{
	t_pipe_group *temp;

	temp = log_grp->pipe_group;
	if (temp->next)
	{
		while(temp->next)
		{
			close(temp->cmd_group->pipes[0]);
			close(temp->cmd_group->pipes[1]);
			temp = temp->next;
		}
	}
}

t_log_group *execute_log(t_data *data, t_log_group *log_grp, int cur_level)
{
	t_log_group *log_temp;
	t_pipe_group *pipe_temp;

	log_temp = log_grp;
	while(log_temp)
	{
		if(log_temp->rec_depth > cur_level)
		{
			log_temp = execute_log(data, log_temp, cur_level + 1);
		}
			if(log_temp->needs == -1 || data->last_log_ret == log_temp->needs)
			{
				pipe_temp = log_temp->pipe_group;
				create_pipes(log_temp);
				while(pipe_temp)
				{
					execute(pipe_temp, data);

					pipe_temp = pipe_temp->next;
				}
				// close_pipes(log_temp);
			}
		if(log_temp->next && log_temp->next->rec_depth < cur_level)
		{
			return log_temp->next;
		}
		log_temp = log_temp->next;
	}
	return NULL;
}

int execution(t_data *data)
{
	int prev_depth;
	
	prev_depth = 0;
	data->pos_paths = find_path(data->envp);
	execute_log(data, data->log_grp, 0);
	return 1;
}