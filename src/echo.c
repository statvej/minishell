/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:55:01 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/22 17:31:44 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minishell.h"

int ft_find(char **args, int *i)
{
	int n;

	n = 0;
	*i = 1;
	if (args[1][0] == '-' && args[1][1] == 'n' && !args[1][2])
	{
		n++;
		*i = 2;
	}
	return (n);
}

int b_echo(char **args)
{
	int i;
	int n;

	n = 0;
	if (!args[1])
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	if (args[1][0] == '-' && args[1][1] == 'n' && !args[1][2] && !args[2])
		return (0);
	n = ft_find(args, &i);
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		i++;
		if (args[i])
			write(1, " ", 1);
	}
	if (!n)
		ft_putstr_fd("\n", 1);
	return (0);
}
