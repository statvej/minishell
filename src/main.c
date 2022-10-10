/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:53:37 by fstaryk           #+#    #+#             */
/*   Updated: 2022/10/10 15:39:56 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


int main(int argc, char **argv, char **envp)
{
	char *comnd_table;
	t_token_list *tokens;
    (void)argc;
	(void)argv;
	(void)envp;

	while (true)
	{
		comnd_table = read_input();
        tokens = lexer(comnd_table);
		print_token(tokens);
		//theExecutor();

		// free_data(data);
	}
	exit(1);
}


	// char **pp = ft_split(readline("type your cmd : "), ' ');
	// int i ;
	// i = fork();
	// if(i == 0)
	// {
	// 	mx_print_strarr(pp, "\n");
	// 	if(!access("/bin/ls", F_OK))
	// 	{
	// 		printf("I");
	// 		execve("/bin/ls", pp, envp);
			
	// 	}
	// }