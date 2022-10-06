/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:53:37 by fstaryk           #+#    #+#             */
/*   Updated: 2022/10/06 15:40:18 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


int main(int argc, char **argv, char **envp)
{
	char *comnd_table;
	t_data *data;
    (void)argc;
	(void)argv;

	while (true)
	{
		comnd_table = read_input();
        data = parse(comnd_table, envp);
		print_data(data);
		//theExecutor();

		free_data(data);
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