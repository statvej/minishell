/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:36:45 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/06 14:26:27 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void    free_strarr(char **strarr)
{
	int i;

	i = 0;
	if(!strarr)
		return;
	while(strarr[i] != NULL)
	{
		free(strarr[i]);
	}
	free(strarr);
}

void free_tokens(t_token_list *tok)
{
	t_token_list *temp;

	if(!tok)
		return;
	temp = tok;
	while (tok)
	{
		tok = tok->next;
		free(temp);
		if(temp->type == EXTENDED)
			free(temp->tok);
		temp = tok;
	}
}

// void free_data(t_data *data)
// {
// 	t_command *temp1;
// 	t_command *temp2;
// 	//free_strarr(data->envp);
// 	if(!data->cmds)
// 		return;
// 	if(!data->cmds->next)
// 		return;
// 	temp1 = data->cmds;
// 	while (temp1)
// 	{
// 		temp2 = temp1->next;
// 		free(temp1);
// 		temp1 = temp2;
// 	}
// }
