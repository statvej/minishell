/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:53:37 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/26 20:30:13 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	shell_loop(int last_ret)
{
	char			*comnd_table;
	t_token_list	*tokens;
	t_data			*data;

	while (true)
	{
		// fprintf(stderr, "\t\t\t\t\tlst ret is %d\n", last_ret);
		comnd_table = read_input();
		if (!comnd_table)
		{
			ft_putstr_fd("\b\bexit", 1);
			exit(1);
		}
		tokens = lexer(comnd_table);
		if (!tokens)
			continue ;
		data = parse(&tokens, last_ret);
		if (!data)
			continue ;
		data->input = comnd_table;
		execution(data);
		// fprintf(stderr, "\t\t\tlst ret is %d\n", data->last_log_ret);
		last_ret = data->last_log_ret;
		free_data_in_loop(data);
	}
}

int	main(int ac, char **av, char **envp)
{
	int				last_ret;

	(void)ac;
	(void)av;
	g_env = create_env(envp);
	last_ret = 0;
	signals();
	shell_loop(last_ret);
	exit(0);
}
