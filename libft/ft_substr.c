/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 11:58:43 by fstaryk           #+#    #+#             */
/*   Updated: 2022/05/03 21:11:54 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ret;
	unsigned long	str_len;

	str_len = ft_strlen(s);
	if (!s)
		return (NULL);
	if (len > str_len)
		len = str_len;
	if (start >= str_len || len <= 0)
		return (ft_calloc(1, 1));
	if (len > str_len && str_len > start)
		len = str_len - start;
	ret = ft_strnew(len);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, &s[start], len + 1);
	return (ret);
}
