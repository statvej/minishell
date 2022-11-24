/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:03:34 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/24 19:13:33 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_data	*parse(t_token_list **global, int last_ret)
{
	t_data	*data;

	if (!global || !g_env)
		return (NULL);
	if (check_lexical_errors(*global) == ERROR)
	{
		perror("Lexical error");
		free_tokens(*global);
		return (NULL);
	}
	extend_wildcards(*global);
	data = (t_data *)malloc(sizeof(t_data));
	data->pos_paths = NULL;
	data->last_log_ret = last_ret;
	data->log_grp = create_log_group(*global);
	set_recursion_depth(data->log_grp);
	create_pipe_group(data->log_grp);
	if (parse_actions(data->log_grp, data) == -1)
	{
		free_data_in_loop(data);
		return (NULL);
	}
	return (data);
}
