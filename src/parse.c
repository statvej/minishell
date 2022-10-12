/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:03:34 by fstaryk           #+#    #+#             */
/*   Updated: 2022/10/12 18:00:57 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"



t_data *parse(t_token_list ** global, char **env)
{
    t_data *data;
	int len = 0;
    
    data = (t_data *)malloc(sizeof(t_data));   
    data->envp = env;
    
	while(token_delim_logic(global, &len))
	{
		printf("\n%d\n", len);
	}
    return NULL;
}
