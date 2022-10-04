/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:03:34 by fstaryk           #+#    #+#             */
/*   Updated: 2022/10/04 17:57:10 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char    **connect_quotes(char **split)
{
	int i;
	int fst;
	int lst;

	i = 0;
	fst = -1;
	lst = -1;
	while (split[i] != NULL)
	{
		if (ft_strchr(split[i], '"') && fst == -1)
		{
			fst = i;
		}
		else if(ft_strchr(split[i], '"'))
		{
			lst = i;
		}
		if(lst && fst)
		{
			i = fst + 1;
			while (fst < lst)
			{
				ft_strjoin();
				i++;
			}
			
		}
		i++;
	}
		
}

t_data *parse(char *input)
{
	char **split;
	t_data	*data;
	t_command	*cmds;
	
	data = (t_data *)malloc(sizeof(data));
	split = ft_split(input, ' ');
	// split = connect_quotes();
	data->(cmds)
	return NULL;
}
