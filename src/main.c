/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:53:37 by fstaryk           #+#    #+#             */
/*   Updated: 2022/10/04 17:29:58 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


int main(int argc, char **argv, char **envp)
{
	char *Comnd_Table;
	s_data data;
    (void)argc;
	(void)argv;
	(void)envp;

	data = initData(envp);
	
	while (true)
	{
		Comnd_Table = read_input();
        //Parser();
		//TheExecutor();

		free(Comnd_Table);
	}
	return (0);
}
