/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pasre_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:44:28 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/10 14:05:32 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int parse_actions(t_log_group *log_grp, t_data *data)
{
	t_log_group *temp;
	t_pipe_group *temp_pipe;
	(void)data;

	temp = log_grp;
	while(temp)
	{
		temp_pipe = temp->pipe_group;
		while(temp_pipe)
		{
			// mx_print_strarr(data->envp, "\n");
			open_extentions(&temp_pipe->tok_list, temp_pipe->tok_len, data->envp);
			open_quotes(&temp_pipe->tok_list, &temp_pipe->tok_len);
			if(!open_redir(temp_pipe))
				return (-1);
            if(!create_args(temp_pipe))
				return (-1);
			// print_cmd(temp_pipe->cmd_group);
			if(temp_pipe)
				temp_pipe = temp_pipe->next;	
		}
		temp = temp->next;
	}
	return (1);
}
