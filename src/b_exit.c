/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:49:06 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/24 18:41:12 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	b_exit(char **av, t_data *data)
{
	int	ac;
	int	i;
	int	exit_status;

	ac = get_str_arr_len(av);
	exit_status = 1;
	if (ac > 2)
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		return (1);
	}
	else if (ac == 1)
		exit_status = 0;
	i = 0;
	while (ac == 2 && av[1][i])
	{
		if (!ft_isdigit(av[1][i]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(av[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit_status = 0;
			break ;
		}
		i++;
	}
	if (exit_status)
		exit_status = ft_atoi(av[1]);
	free_strarr(g_env);
	free_data_in_loop(data);
	clear_history();
	exit(exit_status % 256);
	return (0);
}
