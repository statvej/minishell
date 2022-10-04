/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 11:34:34 by fstaryk           #+#    #+#             */
/*   Updated: 2022/05/02 21:34:43 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned long	count;

	count = 0;
	if (size > 0)
	{
		while ((src[count] != 0) && (count < size - 1))
		{
			dst[count] = src[count];
			count++;
		}
		dst[count] = '\0';
	}
	return (ft_strlen(src));
}
