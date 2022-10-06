/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:53:45 by fstaryk           #+#    #+#             */
/*   Updated: 2022/10/06 15:57:14 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void mx_print_strarr(char **arr, const char *delim){
	if(!arr || !delim){
		return;
	}
	int exist = 0;
	int i = 0;

	for(; arr[i]; i++){
		ft_putstr_fd(arr[i], 1);
		ft_putstr_fd((char *)delim, 1);
		exist = 1;
	}
}

void print_data(t_data *pdata)
{
	int i;
	t_data* data;

	data = pdata;
	if (!data)
	{
		perror("no linklist");
		return ;
	}
	// while(data->envp[i])
	// {
	// 	printf("%s\n", data->envp[i]);
	// 	i++;
	// }
	if (!data->cmds)
	{
		perror("no com");
		return ;	
	}
	printf("\n%d||%d||%d\n",\
		data->in, data->out, data->eout);
	while (data->cmds)
	{
		i = 0;
		printf("Path is %s\n", data->cmds->path);
		while(data->cmds->args[i])
		{
			printf("%s\n", data->cmds->args[i]);
			i++;
		}
		data->cmds = data->cmds->next;
	}
}
