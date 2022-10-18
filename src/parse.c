/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:03:34 by fstaryk           #+#    #+#             */
/*   Updated: 2022/10/18 17:11:58 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"



t_data *parse(t_token_list ** global, char **env)
{
    t_data *data;
    t_log_group *log_grp;

    data = (t_data *)malloc(sizeof(t_data));   
    data->envp = env;
	log_grp = create_log_group(global);
	create_pipe_group(log_grp);
    open_extantion_quotes(log_grp, data);
	print_logic_grp(log_grp);

	
	
    return NULL;
}
