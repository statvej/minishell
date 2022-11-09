/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:13:28 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/09 18:39:29 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_int_list *create_int_link(int val)
{
    t_int_list *ret = (t_int_list *)malloc(sizeof(t_int_list));
    ret->val = val;
    ret->next = NULL;
    return ret;
}


void add_to_int_list(t_int_list **list, t_int_list *to_add)
{
    t_int_list *temp;

    if(!to_add)
        return;
    if(!(*list))
    {
        *list = to_add;
        return;
    }
    temp = *list;
    while (temp->next)
        temp = temp->next;
    temp->next = to_add;   
}

void free_int_list(t_int_list **list)
{
    t_int_list *temp;

    while ((*list))
    {
        temp = (*list);
        free(temp);
        *list = (*list)->next;
    }
}
