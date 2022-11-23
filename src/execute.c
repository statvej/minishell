/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:38:44 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/23 18:13:45 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char **find_path(void)
{
	int		i;
	char	**path;

	i = 0;
	while (ft_strncmp("PATH", g_env[i], 4))
		i++;
	path = ft_split(g_env[i] + 5, ':');
	return (path);
}

char	*find_command(char **path, char *command)
{
	int		i;
	char	*result;	
	char	*temp;
	char	*pwd;
	i = 0;
	//for absolute path
	if(!access(command, F_OK))
		return command;
	//for relative path
	pwd = extend("PWD", 3, 0);
	result = ft_strjoin(pwd, command);
	if(!access(result, F_OK))
	{
		free(pwd);
		return result;
	}
	free(pwd);
	free(result);
	//for path in /bin and similar
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		result = ft_strjoin(temp, command);
		if (!access(result, F_OK))
		{
			free(temp);
			return (result);
		}
		free(temp);
		free(result);
		i++;
	}
	return (0);
}

void process(t_cmd_group *cmd_grp, char **pp)
{
	cmd_grp->command = find_command(pp, cmd_grp->args[0]);
	
	if (!cmd_grp->command)
	{
		perror("command doesn't exist");
	}
	else
		execve(cmd_grp->command, cmd_grp->args, g_env);
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
			if ((dup2(temp_cmd->pipes[1], STDOUT_FILENO)) == -1)
				perror("ERR_OUTFILE");
		if(pipe_grp->prev)
			if ((dup2(pipe_grp->prev->cmd_group->pipes[0], STDIN_FILENO)) == -1)
				perror("ERR_OUTFILE");
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
		if(check_builtin(temp_cmd) != -1)
		{
			if(pipe_grp->next || pipe_grp->prev)
				exit(exec_buin(temp_cmd, data));
		}
		else
			process(temp_cmd, data->pos_paths);
		exit(0);
	}
	else
	{
		if(check_builtin(temp_cmd) && !pipe_grp->next && !pipe_grp->prev)
		{
			data->last_log_ret = exec_buin(temp_cmd, data);
		}
		if(pipe_grp->prev && pipe_grp->prev->cmd_group->pipes[0] > 2)
			close(pipe_grp->prev->cmd_group->pipes[0]);
		if(temp_cmd->pipes[1] > 2)
			close(temp_cmd->pipes[1]);
		// fprintf(stderr, "\n\n\tbefore waitpid\n\n");
		waitpid(temp_cmd->child, &status, 0);
		// print_env();
		
		if(!check_builtin(temp_cmd))
			data->last_log_ret = status;
	}
	//print_env();
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
			if(!log_temp)
				return NULL;
		}
		if(log_temp->needs == -1 ||
				(data->last_log_ret != 256 && log_temp->needs == 1)
					|| (data->last_log_ret == 256 && log_temp->needs == 0))
			{
				pipe_temp = log_temp->pipe_group;
				create_pipes(log_temp);
				while(pipe_temp)
				{
					execute(pipe_temp, data);
					// print_env();
					pipe_temp = pipe_temp->next;
				}
		}
		else if(log_temp->rec_depth != 0)
			return NULL;
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
	data->pos_paths = find_path();
	execute_log(data, data->log_grp, 0);
	return 1;
}