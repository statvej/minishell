/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:26:52 by fstaryk           #+#    #+#             */
/*   Updated: 2022/05/04 12:41:03 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		ind;
	char	*ret;

	ind = 0;
	ret = ft_strnew(ft_strlen(s));
	if (!ret || !s)
		return (NULL);
	while (s[ind])
	{
		ret[ind] = (*f)(ind, s[ind]);
		ind++;
	}
	return (ret);
}
// char	addOne(unsigned int i, char c)
// {
// 	return (i + c);
// }
// int	main(void)
// {
// 	char str[] = "1234";
// 	printf("%s", ft_strmapi(str, addOne));
// }