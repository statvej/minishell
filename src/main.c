/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:53:37 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/10 16:02:38 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


int main(int argc, char **argv, char **envp)
{
	char *comnd_table;
	t_token_list *tokens;
	t_data *data;
	// (void)envp;
    (void)argc;
	(void)argv;
	// char *env_custom[] = {
    //         "HOME=ia doma",
    //         "PWD=/Users/fstaryk/Desktop/minishell",
    //         "SHELL=minishell"};
	while (true)
	{
		comnd_table = read_input();
		fprintf(stderr, "before lexer");
        tokens = lexer(comnd_table);
		if(!tokens)
			continue;
		// print_token(tokens);
		fprintf(stderr, "before parse\n");
		data = parse(&tokens, envp);
		fprintf(stderr, "before exec\n");
	
		execution(data->log_grp->pipe_group, envp);

		// free_data(data);
	}
	exit(1);
}
