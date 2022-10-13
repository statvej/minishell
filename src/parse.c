/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:03:34 by fstaryk           #+#    #+#             */
/*   Updated: 2022/10/13 16:16:50 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"



t_data *parse(t_token_list ** global, char **env)
{
    t_data *data;
	//int l = 0;
    t_log_group *log_grp;

    data = (t_data *)malloc(sizeof(t_data));   
    data->envp = env;
	log_grp = create_log_group(global);
	// log_grp->pipe_group = malloc(sizeof(t_pipe_group));
	// t_pipe_group *pipe_group = log_grp->pipe_group;
	//print_logic_grp(log_grp);
	// while (log_grp)
	// {
	// 	log_grp->pipe_group = malloc(sizeof(t_pipe_group));
		
	// 	while(log_grp->pipe_group)
	// 	{
	// 		fprintf(stderr, "%d\n", log_grp->tok_len);
	// 		printf("%d\n", log_grp->pipe_group->tok_len);
	// 		log_grp->pipe_group->tok_list =token_delim_pipe(log_grp->tok_list, log_grp->tok_len, &log_grp->pipe_group->tok_len);
	// 		printf("%s\n", log_grp->pipe_group->tok_list->tok);
	// 		printf("%d\n", log_grp->pipe_group->tok_len);
	// 		log_grp->pipe_group = log_grp->pipe_group->next;
			
	// 	}
	// 	// while(l < log_grp->pipe_group->tok_len)
	// 	// {
	// 	// 	printf("%s", pipe_group->tok_list->tok);
	// 	// 	pipe_group->tok_list = pipe_group->tok_list->next;
	// 	// }
	// 	log_grp = log_grp->next;
	// }
	
    
    return NULL;
}
