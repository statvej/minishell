/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 11:34:23 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/22 20:09:05 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	// fprintf(stderr, "ia loh ebany before check in func\n");
	if (!ft_isascii(c))
		return ((char *)s);
	// fprintf(stderr, "ia loh ebany before loop in func\n");
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == 0)
		return ((char *)s);
	return (NULL);
}
// int main() {
//     const char str[100] = "lehwrgfu2e";
//     printf("%s", ft_strchr(str, 'g'));
//     return (0);
// }
