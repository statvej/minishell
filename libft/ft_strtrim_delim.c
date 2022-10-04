/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_delim.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:26:52 by fstaryk           #+#    #+#             */
/*   Updated: 2022/05/01 18:06:27 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim_delim(const char *str, char delim)
{
	int		left_spaces;
	int		right_spaces;
	char	*new_string;
	int		i;

	left_spaces = 0;
	right_spaces = 0;
	while (*str == delim)
	{
		str++;
		left_spaces++;
	}
	if (ft_strlen((char *)str) == 0)
		return (0);
	i = ft_strlen((char *)str) - 1;
	while (str[i] == delim)
	{
		right_spaces++;
		i--;
	}
	new_string = ft_strnew(ft_strlen((char *)str) - (left_spaces
				+ right_spaces));
	ft_strncpy(new_string, (char *)str, ft_strlen((char *)str) - right_spaces);
	new_string[ft_strlen(new_string)] = '\0';
	return (new_string);
}
