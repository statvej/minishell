/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:18:13 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/25 16:59:41 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sub_open_quotes(t_token_list **start, t_token_list *temp, int i, int *j)
{
	if (temp->prev && \
			(temp->prev->type == TEXT || temp->prev->type == EXTENDED))
	{
		j[0] = i - 1;
		*start = temp->prev;
	}
	else
	{
		j[0] = i;
		*start = temp;
	}
	if (temp->next && temp->next->len && \
		(temp->next->type == TEXT || temp->next->type == EXTENDED))
		j[1] = i + 1;
	else
		j[1] = i;
}

void	open_quotes(t_token_list **tok_list, int *tok_lenth)
{
	t_token_list	*temp;
	t_token_list	*start;
	int				i;
	int				j[2];

	j[0] = 0;
	j[1] = 0;
	i = 0;
	temp = *tok_list;
	while (temp)
	{
		if (temp->type == DUP_QUOTES || temp->type == SING_QUOTES)
		{
			sub_open_quotes(&start, temp, i, j);
			strtoknjoin(&start, (j[1] - j[0]));
		}
		i++;
		temp = temp->next;
	}
	*tok_lenth -= (j[1] - j[0]);
}
