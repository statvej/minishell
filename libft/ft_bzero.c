/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 11:33:38 by fstaryk           #+#    #+#             */
/*   Updated: 2022/05/02 21:26:45 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *ptr, size_t n)
{
	unsigned char	*temp;
	size_t			i;

	i = 0;
	temp = (unsigned char *)ptr;
	while (i < n)
	{
		*temp = 0;
		temp++;
		i++;
	}
}
// void	ft_bzero(void *s, size_t n)
// {
// 	unsigned char	*p;
// 	size_t			i;

// 	p = (unsigned char *)s;
// 	i = 0;
// 	while (i < n)
// 		p[i++] = '\0';
// }