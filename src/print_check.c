/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:53:45 by fstaryk           #+#    #+#             */
/*   Updated: 2022/10/10 14:47:56 by fstaryk          ###   ########.fr       */
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

void print_token(t_token_list *token)
{
	int i;
	int j;

	i = 0;
	while (token)
	{
		j = 0;
		while (j < token->len)
		{
			fprintf(stderr, "%c", token->tok[j]);
			j++;
		}
		fprintf(stderr, "\n");
		fprintf(stderr, "token type :%d\n", token->type);
		fprintf(stderr, "token lenth :%d\n", token->len);
		i++;
		token = token->next;
	}
	fprintf(stderr, "lenth of list is: %d\n", i);
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
	printf("\n%d||%d||%d||%s||%s\n",\
		data->in, data->out, data->eout, data->file_in, data->file_out);
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
