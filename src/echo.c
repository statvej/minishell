/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchuk <gpinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:55:01 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/25 17:35:54 by gpinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_find(char **args, int *i)
{
	int	j;

	*i = 1;
	while (args[*i])
	{
		j = 0;
		if (args[*i][j++] == '-' && args[*i][j] && args[*i][j] == 'n')
		{
			while (args[*i][j] == 'n')
			{
				j++;
				if (args[*i][j] == '-' && args[*i][j] != 'n')
				{
					*i = 1;
					return ;
				}
			}	
		}
		else
			return ;
		(*i)++;
	}
	return ;
}

void	echo_putstr_fd(char *arg, int fd)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\\')
			i++;
		write(fd, &arg[i], 1);
		i++;
	}
}

int	b_echo(char **args)
{
	int	i;
	int	n;

	n = 0;
	if (!args[1])
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	if (args[1][0] == '-' && args[1][1] == 'n' && !args[1][2] && !args[2])
		return (0);
	ft_find(args, &i);
	if (i > 1)
		n = 1;
	while (args[i])
	{
		echo_putstr_fd(args[i], 1);
		i++;
		if (args[i])
			write(1, " ", 1);
	}
	if (!n)
		ft_putstr_fd("\n", 1);
	return (0);
}
