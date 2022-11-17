/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:03:34 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/17 18:08:13 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"



t_data *parse(t_token_list ** global, char **env)
{
	t_data *data;

	if(!global || !env)
		return NULL;
	if(check_lexical_errors(*global) == ERROR)
	{
		perror("Lexical error");
		return NULL;
	}
	data = (t_data *)malloc(sizeof(t_data));   
	data->envp = env;
	data->log_grp = create_log_group(global);
	set_recursion_depth(data->log_grp);
	create_pipe_group(data->log_grp);
	if(!parse_actions(data->log_grp, data))
		return NULL;
	// print_logic_grp(data->log_grp);
	return data;
}
