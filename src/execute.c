/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yarutiun <yarutiun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:38:44 by fstaryk           #+#    #+#             */
/*   Updated: 2022/12/02 11:25:30 by yarutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	process(t_cmd_group *cmd_grp, char **pp)
{
	cmd_grp->command = find_command(pp, cmd_grp->args[0]);
	if (!cmd_grp->command)
	{
		perror("command doesn't exist");
		exit(1);
	}
	else
		execve(cmd_grp->command, cmd_grp->args, g_env);
}

int	create_pipes(t_log_group *log_grp)
{
	t_pipe_group	*temp;

	temp = log_grp->pipe_group;
	if (temp->next)
	{
		while (temp->next)
		{
			if (pipe(temp->cmd_group->pipes) == -1)
				return (0);
			temp = temp->next;
		}		
	}
	return (1);
}

void	redirect_pipes(t_cmd_group	*temp_cmd, t_pipe_group *pipe_grp)
{
	if (pipe_grp->next)
		if ((dup2(temp_cmd->pipes[1], STDOUT_FILENO)) == -1)
			perror("ERR_OUTFILE");
	if (pipe_grp->prev)
		if ((dup2(pipe_grp->prev->cmd_group->pipes[0], STDIN_FILENO)) == -1)
			perror("ERR_OUTFILE");
	while (temp_cmd->in)
	{
		dup2(temp_cmd->in->val, STDIN_FILENO);
		temp_cmd->in = temp_cmd->in->next;
	}
	while (temp_cmd->out)
	{
		dup2(temp_cmd->out->val, STDOUT_FILENO);
		temp_cmd->out = temp_cmd->out->next;
	}
}

void	close_pipes(t_pipe_group *pipe_grp)
{
	while (pipe_grp)
	{
		if (pipe_grp->cmd_group->pipes[0] > 2)
			close(pipe_grp->cmd_group->pipes[0]);
		if (pipe_grp->cmd_group->pipes[1] > 2)
			close(pipe_grp->cmd_group->pipes[0]);
		pipe_grp = pipe_grp->next;
	}
}

int	execution(t_data *data)
{
	data->pos_paths = find_path();
	execute_log(data, data->log_grp, 0);
	return (1);
}
