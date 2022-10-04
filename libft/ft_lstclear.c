/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: statvej <statvej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 20:49:08 by fstaryk           #+#    #+#             */
/*   Updated: 2022/05/05 13:51:44 by statvej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*temp_next;

	temp = *lst;
	while (temp)
	{
		temp_next = temp->next;
		(*del)(temp->content);
		free(temp);
		temp = temp_next;
	}
	*lst = NULL;
}
// int main() {
//     t_list* l = ft_lstnew(malloc(1));
//     for (int i = 0; i < 10; ++i)
//         ft_lstadd_front(&l, ft_lstnew(malloc(1)));
//     ft_lstclear(&l, free);
// }
