/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:36:32 by fstaryk           #+#    #+#             */
/*   Updated: 2022/10/05 15:49:47 by fstaryk          ###   ########.fr       */
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
	ret = (char **)ft_calloc(sizeof(char *), size + 2);// +2 for new elem and null
	strarr_cpy(ret, strarr);
	ret[size] = ft_strdup(str);
	free_strarr(strarr);
	return ret;
}

// char	*ft_strjoin_del1(char const *s1, char const *s2)
// {
// 	char	*tmp;

// 	if (s1 && s2)
// 	{
// 		tmp = ft_strnew(ft_strlen((char *)s1) + ft_strlen((char *)s2));
// 		if (!tmp)
// 			return (NULL);
// 		tmp = ft_strcpy(tmp, (char *)s1);
// 		free(s1);
// 		return (ft_strcat(tmp, (char *)s2));
// 	}
// 	else if (s1 == NULL && s2 != NULL)
// 		return (ft_strdup((char *)s2));
// 	else if (s2 == NULL && s1 != NULL)
// 		return (ft_strdup((char *)s1));
// 	else
// 		return (NULL);
// }

void print_data(t_command *data)
{
	t_command	*temp;
	int i;

	if (!data)
		{
			perror("no linklist");
			return ;
		}
	temp = data;
	while (temp->next)
	{
		i = 0;
		printf("%s, \n %d||%d||%d\n", temp->path,\
		temp->data->in, temp->data->out, temp->data->eout);
		while(temp->args[i])
		{
			printf("%s\n", temp->args[i]);
			i++;
		}
		i = 0;
		while(temp->data->envp[i])
		{
			printf("%s\n", temp->args[i]);
			i++;
		};
		temp = temp->next;
	}
}
