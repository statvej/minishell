/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:03:34 by fstaryk           #+#    #+#             */
/*   Updated: 2022/10/05 15:57:40 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// char    **connect_quotes(char **split)
// {
// 	int i;
// 	int fst;
// 	int lst;

// 	i = 0;
// 	fst = -1;
// 	lst = -1;
// 	while (split[i] != NULL)
// 	{
// 		if (ft_strchr(split[i], '"') && fst == -1)
// 		{
// 			fst = i;
// 		}
// 		else if(ft_strchr(split[i], '"'))
// 		{
// 			lst = i;
// 		}
// 		if(lst && fst)
// 		{
// 			i = fst + 1;
// 			while (fst < lst)
// 			{
// 				ft_strjoin();
// 				i++;
// 			}
			
// 		}
// 		i++;
// 	}
		
// }


t_data *parse(char *input, char **envp)
{
	char **split;
	t_data	*data;
	// t_command	*cmds;
	char **strarr;
	// int quotes;
	int i;
	
	
	data = init_data(envp);
	split = ft_split(input, ' ');
	// quotes = CLOSED;
	i = 0;
	strarr = NULL;
	mx_print_strarr(split, "\n");
	while(split[i])
	{
		if (ft_strcmp(split[i], "|"))
		{
			add_command(&data->cmds, create_command(NULL, strarr, data));
	fprintf(stderr, "CHECK!\n");
			free_strarr(strarr);
			strarr = NULL;
		}
		strarr = add_elem_to_strarr(strarr, split[i]);
		i++;
	}
	add_command(&data->cmds, create_command(NULL, strarr, data));
	free_strarr(strarr);
	// split = connect_quotes();
	
	return data;
}
