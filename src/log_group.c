/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_group.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 17:36:08 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/24 19:16:44 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//added restoration of global token
t_log_group	*create_log_group(t_token_list *global)
{
	t_log_group		*ret;
	int				len;
	int				needs;
	t_token_list	*temp_tok;

	if (!global)
		return (NULL);
	ret = NULL;
	temp_tok = token_delim_logic(global, &len, &needs);
	while (temp_tok)
	{
		add_log_link(&ret, create_log_link(temp_tok, len, needs));
		temp_tok = token_delim_logic(global, &len, &needs);
	}
	//to reset values
	token_delim_logic(NULL, NULL, NULL);
	// restore_tok_list(global);
	return (ret);
}

t_log_group	*create_log_link(t_token_list *tok_list, int tok_len, int needs)
{
	t_log_group	*log_link;

	log_link = (t_log_group *)malloc(sizeof(t_log_group));
	log_link->tok_list = tok_list;
	log_link->tok_len = tok_len;
	log_link->next = NULL;
	log_link->prev = NULL;
	log_link->pipe_group = NULL;
	log_link->rec_depth = 0;
	log_link->needs = needs;
	return (log_link);
}

void	add_log_link(t_log_group **first, t_log_group *to_add)
{
	t_log_group	*temp;

	if (!to_add)
		return ;
	if (!(*first))
	{
		*first = to_add;
		return ;
	}
	temp = *first;
	while (temp->next)
		temp = temp->next;
	temp->next = to_add;
	to_add->prev = temp;
}
