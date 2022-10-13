/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:53:45 by fstaryk           #+#    #+#             */
/*   Updated: 2022/10/13 13:30:45 by fstaryk          ###   ########.fr       */
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

void print_ntoken(t_token_list *token, int n)
{
	int i;
	int j;

	i = 0;
	while (token && i < n)
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

void print_logic_grp(t_log_group *log_grp)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (log_grp)
	{
		i = 0;
		printf("%d\n", log_grp->tok_len);
		print_ntoken(log_grp->tok_list, log_grp->tok_len);
		printf("\n");
		log_grp = log_grp->next;
	}
}
