/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:35:57 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/25 17:55:34 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token_list	*create_token(int length, char *start, int type)
{
	t_token_list	*token;

	if (!length && !(type == DUP_QUOTES || type == SING_QUOTES))
		return (NULL);
	token = (t_token_list *)malloc(sizeof(t_token_list));
	token->len = length;
	token->next = NULL;
	token->prev = NULL;
	token->tok = start;
	token->type = type;
	return (token);
}

void	add_token(t_token_list **first, t_token_list *to_add)
{
	t_token_list	*temp;

	if (!to_add)
	{
		return ;
	}
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

void	insert_token_after(t_token_list *insert_ref, t_token_list *to_add)
{
	t_token_list	*insert_next;

	insert_next = insert_ref->next;
	insert_ref->next = to_add;
	to_add->prev = insert_ref;
	to_add->next = insert_next;
	if (insert_next)
		insert_next->prev = to_add;
}

t_token_list	*skip_n_token(t_token_list *global, int count)
{
	int	i;

	i = 0;
	while (i < count && global)
	{
		i++;
		global = global->next;
	}
	return (global);
}

void	restore_tok_list(t_token_list **global)
{
	while ((*global)->prev)
		(*global) = (*global)->prev;
}
