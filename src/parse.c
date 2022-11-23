/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:03:34 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/23 18:09:58 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"



t_data *parse(t_token_list ** global, int last_ret)
{
	t_data *data;

	if(!global || !g_env)
		return NULL;
	if(check_lexical_errors(*global) == ERROR)
	{
		perror("Lexical error");
		return NULL;
	}
	data = (t_data *)malloc(sizeof(t_data));  
	data->last_log_ret = last_ret;
	data->log_grp = create_log_group(*global);
	set_recursion_depth(data->log_grp);
	create_pipe_group(data->log_grp);
	if(!parse_actions(data->log_grp, data))
		return NULL;
	extend_wildcards(*global);
	// print_token(*global);
	// print_logic_grp(data->log_grp);
	return data;
}
