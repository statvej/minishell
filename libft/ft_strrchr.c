/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 11:34:53 by fstaryk           #+#    #+#             */
/*   Updated: 2022/05/02 21:34:51 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*ret;

	if (!ft_isascii(c))
		return ((char *)s);
	ret = NULL;
	while (*s)
	{
		if (*s == c)
			ret = s;
		s++;
	}
	if (c == 0)
		return ((char *)s);
	return ((char *)ret);
}
// int main() {
//     const char str[100] = "glehwrgfu2e";
//     printf("%s", ft_strrchr(str, 'g'));
//     return (0);
// }
