/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:31:04 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/22 17:06:02 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char **delete_env(int index)
{
	char	*tmp;
	int	size;

	size = size_of_env();
	while (g_env[index + 1])
	{
		tmp = ft_strdup(g_env[index + 1]);
		free(g_env[index]);
		g_env[index] = tmp;
		index++;
	}
	return (realloc_env((size - 1)));
}

int b_unset(char **args)
{
	int i;
	int j;

	i = 0;
	while(args[i])
	{
		j = find_keyword(args[i]);
		if (j != -1 && g_env[j])
			g_env = delete_env(j);
		else
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}