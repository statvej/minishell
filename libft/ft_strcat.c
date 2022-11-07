/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:32:05 by statvej           #+#    #+#             */
/*   Updated: 2022/11/07 18:01:05 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int		index;
	size_t	i;

	index = ft_strlen(s1);
	i = 0;
	while (i < ft_strlen((char *)s2))
	{
		s1[index] = s2[i];
		i++;
		index++;
	}
	s1[index] = '\0';
	return (s1);
}
// int main(){
//     char str1[100] = "Qwert";
//     char str2[100] = "1234";
//     ft_strcat(str1, str2);
//     printf("%s", str1);
// }
