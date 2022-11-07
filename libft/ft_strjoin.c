/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:45:04 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/07 18:01:25 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tmp;
	char 	*test;

	if (s1 && s2)
	{
		tmp = ft_strnew(ft_strlen((char *)s1) + ft_strlen((char *)s2));
		if (!tmp)
			return (NULL);
		tmp = ft_strcpy(tmp, (char *)s1);
		test = ft_strcat(tmp, (char *)s2);
		return (test);
	}
	else if (s1 == NULL && s2 != NULL)
		return (ft_strdup((char *)s2));
	else if (s2 == NULL && s1 != NULL)
		return (ft_strdup((char *)s1));
	else
		return (NULL);
}

// int	main(void)
// {
// 	// char str1[100] = "";
// 	// char str2[100] = "";
// 	printf("%s", ft_strjoin(NULL, NULL));
// }