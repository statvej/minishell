/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:54:55 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/22 20:16:20 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int check_keyword(char *args)
{
	int i;
	short int index;

	i = 0;
	index = 0;
	if(!args || !args[0] || args[0] == '=')
		return (1);
	while (args[i] && args[i] != '=')
	{
		if (ft_isalpha(args[i]))
			index = 1;
		else
			if (ft_isdigit(args[i]) && !index)
				return (1);
			else if (args[i] != '_')
				return (1);
		i++;
	}
	return (0);
}

void change_env(char *arg, int index)
{
	free(g_env[index]);
	g_env[index] = ft_strdup(arg);
	free(arg);
}

void set_new(char *arg)
{
	char	*end;
	char	*st;
	size_t	count;

	end = NULL;
	count = size_of_env() + 1;
	g_env = realloc_env(count);
	if (!(st = ft_substr(arg, 0,
		find_index_of_char(arg, '=') + 1)))
		return ;
	if (!(end = ft_substr(arg,
		find_index_of_char(arg, '=') + 1, ft_strlen(arg))))
	{
		free(st);
		return ;
	}
	g_env[count - 1] = ft_strjoin(st, end);
	free(st);
	free(end);
}


void add_env(char *arg)
{
	int indx;
	char *sub;

	if((indx = find_index_of_char(arg, '=')) == -1)
		indx = ft_strlen(arg);
	sub = ft_substr(arg, 0, indx);
	indx = find_keyword(sub);
	free(sub);
	if(indx == -1)
		set_new(arg);
	else
		change_env(arg, indx);
}

int b_export(char **args)
{
	int i;

	if (!args[0])
	{
		//print_export();
		printf("I");
		return(1);
	}
	i = 0;
	while(args[i])
	{
		if(check_keyword(args[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (1);
		}
		add_env(args[i]);
		i++;
	}
	return (0);
}