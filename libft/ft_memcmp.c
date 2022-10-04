/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:10:38 by fstaryk           #+#    #+#             */
/*   Updated: 2022/04/27 16:34:12 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				result;
	unsigned char	*us1;
	unsigned char	*us2;
	unsigned char	*end;

	result = 0;
	if (s1 != s2)
	{
		us1 = (unsigned char *)s1;
		us2 = (unsigned char *)s2;
		end = (unsigned char *)us1 + n;
		while (!result && us1 != end)
			result = *us1++ - *us2++;
	}
	return (result);
}
// int	main(void)
// {
// 	char str1[100] = "qwe33rty";
// 	char str2[100] = "qwerty";
// 	printf("%d", ft_memcmp((void *)str1, (void *)str2, 4));
// }
