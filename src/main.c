/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:53:37 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/19 17:32:54 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"



int main(int argc, char **argv, char **envp)
{
	char *comnd_table;
	t_token_list *tokens;
	t_data *data;
	int last_ret;
	(void)argc;
	(void)argv;
	// signal(SIGQUIT, sig_handle);
	// signal(SIGINT, sig_handle);
	g_env = create_env(envp);
	last_ret = 0;
	while (true)
	{
		// printf("\033[0;36m");
		comnd_table = read_input();
		// printf("\033[0m");
        tokens = lexer(comnd_table);
		if(!tokens)
			continue;
		data = parse(&tokens, last_ret);
		if(!data)
		{
			free_tokens(tokens);
			continue;
		}
		execution(data);
		free_data_in_loop(data);
		// exit(0);
	}

	
	exit(1);
}
