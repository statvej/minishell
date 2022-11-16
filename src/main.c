/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:53:37 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/16 18:07:26 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


int main(int argc, char **argv, char **envp)
{
	char *comnd_table;
	t_token_list *tokens;
	t_data *data;
    char **env;
	(void)argc;
	(void)argv;
	// char *env_custom[] = {
    //         "HOME=ia doma",
    //         "PWD=/Users/fstaryk/Desktop/minishell",
    //         "SHELL=minishell"};

	// signal(SIGQUIT, sig_handle);
	// signal(SIGINT, sig_handle);
	// env = set_env();
	while (true)
	{
		comnd_table = read_input();
        tokens = lexer(comnd_table);
		if(!tokens)
			continue;
		data = parse(&tokens, envp);
		if(!data)
			continue;
		execution(data);
		env = data->envp;
		free(comnd_table);
	}
	exit(1);
}
