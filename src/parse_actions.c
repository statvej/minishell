/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:44:28 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/26 20:27:40 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	parse_actions(t_log_group *log_grp, t_data *data)
{
	t_log_group		*temp;
	t_pipe_group	*temp_pipe;

	temp = log_grp;
	while (temp)
	{
		temp_pipe = temp->pipe_group;
		while (temp_pipe)
		{
			open_extentions(&temp_pipe->tok_list, temp_pipe->tok_len, \
														data->last_log_ret);
			open_quotes(&temp_pipe->tok_list, &temp_pipe->tok_len);
			if (open_redir(temp_pipe) == -1)
				return (-1);
			if (create_args(temp_pipe) == -1)
				return (-1);
			if (temp_pipe)
				temp_pipe = temp_pipe->next;
		}
		temp = temp->next;
	}
	// print_logic_grp(log_grp);
	return (1);
}
