/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 12:20:42 by fstaryk           #+#    #+#             */
/*   Updated: 2022/05/10 15:53:46 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret_lst;
	t_list	*new_node;

	if (!lst)
		return (NULL);
	ret_lst = NULL;
	while (lst)
	{
		new_node = ft_lstnew((*f)(lst->content));
		if (!new_node)
		{
			del(new_node);
		}
		ft_lstadd_back(&ret_lst, new_node);
		lst = lst->next;
	}
	return (ret_lst);
}
