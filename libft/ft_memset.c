/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 11:34:21 by fstaryk           #+#    #+#             */
/*   Updated: 2022/05/01 18:17:32 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int x, int n)
{
	unsigned char	*temp;
	int				i;

	i = 0;
	temp = (unsigned char *)ptr;
	while (i < n)
	{
		*temp = x;
		temp++;
		i++;
	}
	return (ptr);
}
