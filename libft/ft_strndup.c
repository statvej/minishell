/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:48:48 by fstaryk           #+#    #+#             */
/*   Updated: 2022/05/01 18:34:51 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*cpy;

	if (ft_strlen((char *)s1) < n)
		cpy = ft_strnew(ft_strlen((char *)s1));
	else
		cpy = ft_strnew(n);
	if (cpy == NULL)
		return (NULL);
	return (ft_strncpy(cpy, (char *)s1, n));
}
