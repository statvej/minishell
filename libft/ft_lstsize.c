/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: statvej <statvej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 20:18:43 by fstaryk           #+#    #+#             */
/*   Updated: 2022/05/05 13:52:45 by statvej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*temp;
	int		count;

	if (!lst)
		return (0);
	temp = lst;
	count = 0;
	while (temp->next)
	{
		count++;
		temp = temp->next;
	}
	count++;
	return (count);
}
// int main() {
//     t_list* l = NULL;
//     ft_lstadd_front(&l, ft_lstnew((void*)2));
//     ft_lstadd_front(&l, ft_lstnew((void*)2));
//     fprintf(stderr, "%d", ft_lstsize(l));
// }