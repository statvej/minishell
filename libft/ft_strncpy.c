/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 10:14:38 by fstaryk           #+#    #+#             */
/*   Updated: 2022/05/05 13:43:37 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t len)
{
	size_t		index;
	size_t		src_len;

	src_len = ft_strlen(src);
	index = 0;
	while (index < len)
	{
		if (index <= src_len)
			dest[index] = src[index];
		else
			dest[index] = '\0';
		index++;
	}
	return (dest);
}
