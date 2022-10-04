/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:10:05 by fstaryk           #+#    #+#             */
/*   Updated: 2022/05/04 13:01:06 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	is_char_in_str(const char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (true);
		str++;
	}
	return (false);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		c_str;
	int		c_fin;
	int		fin_len;
	char	*ret;

	fin_len = 0;
	c_str = 0;
	c_fin = ft_strlen(s1) - 1;
	while (is_char_in_str(set, s1[c_str]) && c_fin <= (int)ft_strlen(s1))
		c_str++;
	while (is_char_in_str(set, s1[c_fin]) && c_fin >= 0)
		c_fin--;
	if (c_fin <= 0 || c_str == (int)ft_strlen(s1) - 1)
		return (ft_calloc(1, 1));
	fin_len = c_fin - c_str + 2;
	ret = ft_strnew(fin_len);
	ft_strlcpy(ret, (char *)(&s1[c_str]), fin_len);
	return (ret);
}

// int	main(void)
// {
// 	//char	str1[] = "\t\t    weiylrg   \n\n";
// 	char * s = ft_strtrim("   xxxtripouille", " x");
// 	printf("%s", s);
// }
