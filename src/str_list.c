/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:53:49 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/24 19:09:57 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//string should already be malloced
t_str_list	*create_str_link(char *str, int len, int strict)
{
	t_str_list	*ret;

	ret = (t_str_list *)malloc(sizeof(t_str_list));
	ret->str = str;
	ret->len = len;
	ret->strict = strict;
	ret->next = NULL;
	return (ret);
}

void	add_to_str_list(t_str_list **list, t_str_list *to_add)
{
	t_str_list	*temp;

	if (!to_add)
		return ;
	if (!(*list))
	{
		*list = to_add;
		return ;
	}
	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = to_add;
}

void	free_str_list(t_str_list **list)
{
	t_str_list	*temp;
	t_str_list	*start;

	if (!list)
		return ;
	start = (*list);
	while ((*list))
	{
		temp = (*list);
		if (temp->str)
			free(temp->str);
		free(temp);
		*list = (*list)->next;
	}
	start = NULL;
}
