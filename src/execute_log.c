/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_log.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:18:18 by gpinchuk          #+#    #+#             */
/*   Updated: 2022/11/26 20:30:13 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	parent_process(t_data *data, t_cmd_group *temp_cmd, \
										t_pipe_group *pipe_grp)
{
	int			status;

	if (check_builtin(temp_cmd) && !pipe_grp->next && !pipe_grp->prev)
	{
		data->last_log_ret = exec_buin(temp_cmd, data);
		// fprintf(stderr, "\t\t\tCHECK buin\n");
	}
	if (pipe_grp->prev && pipe_grp->prev->cmd_group->pipes[0] > 2)
		close(pipe_grp->prev->cmd_group->pipes[0]);
	if (temp_cmd->pipes[1] > 2)
		close(temp_cmd->pipes[1]);
	waitpid(temp_cmd->child, &status, 0);
	if (!check_builtin(temp_cmd))
	{
		// fprintf(stderr, "\t\t\tCHECK status is %d\n", status);
		data->last_log_ret = status;
	}
}

void	execute(t_pipe_group *pipe_grp, t_data *data)
{
	t_cmd_group	*temp_cmd;

	temp_cmd = pipe_grp->cmd_group;
	temp_cmd->child = fork();
	if (temp_cmd->child == 0)
	{
		child_sig();
		redirect_pipes(temp_cmd, pipe_grp);
		if (check_builtin(temp_cmd))
		{
			if (pipe_grp->next || pipe_grp->prev)
				exit(exec_buin(temp_cmd, data));
		}
		else
			process(temp_cmd, data->pos_paths);
		exit(0);
	}
	else
		parent_process(data, temp_cmd, pipe_grp);
}

int	sub_execute_log(t_pipe_group **pipe_temp, \
					t_data *data, t_log_group	*log_temp)
{
	*pipe_temp = log_temp->pipe_group;
	if (!create_pipes(log_temp))
	{
		perror("Bro, why do you need so many pipes???\n");
		close_pipes(*pipe_temp);
		return (0);
	}
	while (*pipe_temp)
	{
		execute(*pipe_temp, data);
		*pipe_temp = (*pipe_temp)->next;
	}
	return (1);
}

int	sub_execute_log_recursion(t_log_group **log_grp, t_data *data, \
														int cur_level)
{
	*log_grp = execute_log(data, *log_grp, cur_level + 1);
	if (*log_grp)
		return (1);
	else
		return (0);
}

t_log_group	*execute_log(t_data *data, t_log_group *log_grp, int cur_level)
{
	t_log_group		*lt;
	t_pipe_group	*pipe_temp;
	int				lock;

	lt = log_grp;
	lock = OPENED;
	while (lt)
	{
		if (lt->rec_depth > cur_level)
			if (!sub_execute_log_recursion(&lt, data, cur_level))
				return (NULL);
		if (lt->needs == -1 || (data->last_log_ret != 256 && lt->needs == 1) \
			|| (data->last_log_ret == 256 && lt->needs == 0))
		{
			if (lock == OPENED && !(sub_execute_log(&pipe_temp, data, lt)))
				return (NULL);
		}
		else if (lt->rec_depth != 0 && lt->prev && \
						lt->prev->rec_depth != cur_level)
			lock = CLOSED;
		if (lt->next && lt->next->rec_depth < cur_level)
			return (lt->next);
		lt = lt->next;
	}
	return (NULL);
}
