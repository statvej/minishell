/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:26:49 by fstaryk           #+#    #+#             */
/*   Updated: 2022/07/21 12:46:27 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_words(const char *str, char c)
{
	int	prev_separator;
	int	words;

	if (!str)
	{
		return (-1);
	}
	prev_separator = 0;
	words = 0;
	while (*str)
	{
		if (*str == c)
		{
			prev_separator = 0;
		}
		else if (prev_separator == 0)
		{
			prev_separator = 1;
			words++;
		}
		str++;
	}
	return (words);
}

static int	get_word_length(const char *s, char c)
{
	int		word_length;
	char	*copy_s;

	word_length = 0;
	copy_s = (char *)s;
	while ((*copy_s != c) && (*copy_s != '\0'))
	{
		word_length++;
		copy_s++;
	}
	return (word_length);
}

char	**ft_split(const char *s, char c)
{
	int		word_length;
	int		i;
	char	**arr;

	word_length = 0;
	i = 0;
	arr = NULL;
	if (!s)
		return (NULL);
	arr = (char **)malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	while (*s)
	{
		if (*s != c)
		{
			word_length = get_word_length(s, c);
			arr[i] = ft_strndup(s, word_length);
			s += word_length;
			i++;
			continue ;
		}
		s++;
	}
	arr[i] = NULL;
	return (arr);
}
