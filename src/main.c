/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:53:37 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/24 19:40:27 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char			*comnd_table;
	t_token_list	*tokens;
	t_data			*data;
	int				last_ret;

	(void)ac;
	(void)av;
	g_env = create_env(envp);
	last_ret = 0;
	while (true)
	{
		comnd_table = read_input();
		tokens = lexer(comnd_table);
		if (!tokens)
			continue ;
		data = parse(&tokens, last_ret);
		if (!data)
			continue ;
		data->input = comnd_table;
		execution(data);
		free_data_in_loop(data);
	}
	exit(1);
}
