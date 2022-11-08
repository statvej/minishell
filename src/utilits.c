/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:36:32 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/08 14:05:06 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_str_arr_len(char **strarr)
{
	int i;

	if(!strarr)
		return 0;
	i = 0;
	while (strarr[i] != NULL)
		i++;
	return i;
}

void strarr_cpy(char **dst, char **src)
{
	if(!dst | !src)
		return;
	while (*dst && *src)
	{
		*dst = ft_strdup(*src);
		dst++;
		src++;
	}
}

char ** add_elem_to_strarr(char **strarr, char *str)
{
	int size;
	char **ret;
	
	size = get_str_arr_len(strarr);
	ret = (char **)malloc(sizeof(char *) * (size + 2));// +2 for new elem and null
	strarr_cpy(ret, strarr);
	ret[size] = ft_strdup(str);
	ret[size + 1] = NULL;
	mx_print_strarr(ret, "|");
	// free_strarr(strarr);
	return ret;
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
		return tmp;
	}
	else if (s1 == NULL && s2 != NULL)
		return (ft_strndup((char *)s2, n2));
	else if (s2 == NULL && s1 != NULL)
		return (ft_strndup((char *)s1, n1));
	else
		return (NULL);
}

void strtoknjoin(t_token_list **start, int lenth)
{
	int i;
	t_token_list *temp;
	t_token_list *temp_free;
	t_token_list *ret;
	char *elem;

	temp = NULL;
	elem = NULL;
	if((*start)->prev)
		temp = (*start)->prev;
	i = 0;

	if(!(lenth == 0 && (*start)->len == 0))
	{
		while(i <= lenth)
		{
			
			elem = ft_strnnjoin(elem, (int)ft_strlen(elem), (*start)->tok, (*start)->len);
			if((*start)->type == EXTENDED)
				free((*start)->tok);
			temp_free = *start;
			*start = (*start)->next;
			if(temp_free)
				free(temp_free);
			i++;
		}
		ret = create_token(ft_strlen(elem), elem, EXTENDED);
		if (temp)
			temp->next = ret;
		ret->prev = temp;
		//because start is already start next
		if ((*start))
		{
			ret->next = (*start);
			ret->next->prev = ret;
		}
	}
	// restore_tok_list(start);
	fprintf(stderr, "poopoo\n");
}