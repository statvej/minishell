/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:04:12 by fstaryk           #+#    #+#             */
/*   Updated: 2022/04/27 16:41:48 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			length;
	unsigned char	us_c;
	unsigned char	*temp;

	length = 0;
	us_c = (unsigned char)c;
	temp = (unsigned char *)s;
	while (length < n)
	{
		if (*temp == us_c)
		{
			return ((void *)temp);
		}
		temp++;
		length++;
	}
	return (NULL);
}
// int main() {
//     const char str[100] = "lehwrgfu2e";
//     printf("%s", ft_memchr(NULL, 'g', 10));
//     return (0);
// }
