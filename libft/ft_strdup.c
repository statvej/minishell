/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 11:34:29 by fstaryk           #+#    #+#             */
/*   Updated: 2022/04/27 14:39:05 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*new_string;

	new_string = (char *)malloc(ft_strlen((char *)str) * sizeof(char));
	ft_strcpy(new_string, str);
	return (new_string);
}
