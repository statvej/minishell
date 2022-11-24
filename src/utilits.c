/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:36:32 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/24 19:05:34 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_str_arr_len(char **strarr)
{
	int	i;

	if (!strarr)
		return (0);
	i = 0;
	while (strarr[i] != NULL)
		i++;
	return (i);
}

char	*ft_strnnjoin(char const *s1, int n1, char const *s2, int n2)
{
	char	*tmp;

	if (s1 && s2)
	{
		tmp = ft_strnew(n1 + n2);
		if (!tmp)
			return (NULL);
		tmp = ft_strncpy(tmp, (char *)s1, n1);
		ft_strlcat(tmp, (char *)s2, n1 + n2 + 1);
		return (tmp);
	}
	else if (s1 == NULL && s2 != NULL)
		return (ft_strndup((char *)s2, n2));
	else if (s2 == NULL && s1 != NULL)
		return (ft_strndup((char *)s1, n1));
	else
		return (NULL);
}

void	strtoknjoin(t_token_list **start, int lenth)
{
	int				i;
	t_token_list	*temp;
	t_token_list	*ret;
	char			*elem;
	char			*to_free;

	temp = NULL;
	elem = NULL;
	if ((*start)->prev)
		temp = (*start)->prev;
	i = 0;
	if (!(lenth == 0 && (*start)->len == 0))
	{
		while (i <= lenth)
		{
			to_free = elem;
			elem = ft_strnnjoin(elem, (int)ft_strlen(elem), \
					(*start)->tok, (*start)->len);
			if (to_free)
				free(to_free);
			if ((*start)->type == EXTENDED)
				free((*start)->tok);
			ret = *start;
			*start = (*start)->next;
			if (ret)
				free(ret);
			i++;
		}
		ret = create_token(ft_strlen(elem), elem, EXTENDED);
		if (temp)
			temp->next = ret;
		ret->prev = temp;
		if (*start)/*because start is already start next*/
		{
			ret->next = (*start);
			ret->next->prev = ret;
		}
	}
}
