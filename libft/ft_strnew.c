/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:41:55 by fstaryk           #+#    #+#             */
/*   Updated: 2022/04/27 14:41:58 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(const int size)
{
	int		i;
	char	*new_string;

	if (size < 0)
	{
		return (0);
	}
	i = 0;
	new_string = (char *)malloc(sizeof(char) * (size + 1));
	while (i <= size)
	{
		new_string[i] = '\0';
		i++;
	}
	return (new_string);
}
