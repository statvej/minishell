/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_lower.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 18:51:42 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/19 18:55:48 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_string_lower(char *str)
{
	char	*ret;

	if (!str)
		return (NULL);
	ret = str;
	while (*str)
	{
		ft_tolower(*str);
		str++;
	}
	return (str);
}
