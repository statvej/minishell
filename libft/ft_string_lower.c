/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_lower.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yarutiun <yarutiun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 18:51:42 by fstaryk           #+#    #+#             */
/*   Updated: 2022/12/02 11:28:06 by yarutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_string_lower(char *str)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		ft_tolower(*str);
		str++;
	}
	return (str);
}
