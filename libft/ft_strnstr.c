/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 11:34:43 by fstaryk           #+#    #+#             */
/*   Updated: 2022/05/04 12:57:15 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	co;
	size_t	unt;
	char	*temo;

	temo = (char *)haystack;
	co = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (*temo && co < len)
	{
		unt = 0;
		while (temo[co + unt] == needle[unt] && len - co >= ft_strlen(needle))
		{
			if (needle[unt + 1] == '\0')
			{
				return (&temo[co]);
			}
			unt++;
		}
		co++;
	}
	return (0);
}
// int main(){
//     char str1[100] = "ewytcwevihqwertyh2hvrrhgfv32r";
//     char str2[100] = "qwer2e";
//     printf("%s", ft_strnstr(str1, str2, 4));
// }