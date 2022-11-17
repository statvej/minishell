/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:53:45 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/17 17:52:51 by fstaryk          ###   ########.fr       */
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
		fprintf(stderr, "%s%s", arr[i], delim);
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

void print_ntoken(t_token_list *token, int n, char * depth)
{
	int i;
	int j;

	i = 0;
	while (token && i < n)
	{
		j = 0;
		fprintf(stderr, "%s", depth);
		while (j < token->len)
		{
			fprintf(stderr, "%c", token->tok[j]);
			j++;
		}
		fprintf(stderr, "\n");
		fprintf(stderr, "%stoken type :%d\n", depth, token->type);
		fprintf(stderr, "%stoken lenth :%d\n\n", depth, token->len);
		i++;
		token = token->next;
	}
	fprintf(stderr, "\n%slenth of list is: %d\n\n", depth, i);
}

void print_pipe_group(t_pipe_group *pipe_grp)
{
	int i;

	i = 0;
	printf("\n\tpipe groups incoming\n\n");
	while (pipe_grp)
	{
		printf("pipe link #%d\n", i);
		// print_ntoken(pipe_grp->tok_list, pipe_grp->tok_len, "\t");
		print_cmd(pipe_grp->cmd_group);
		pipe_grp = pipe_grp->next;
		i++;
	}	
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
		printf("tokens in group %d\n", log_grp->tok_len);
		// print_ntoken(log_grp->tok_list, log_grp->tok_len, "");
		printf("\n");
		printf("group needs %d", log_grp->needs);
		printf("\n");
		printf("recursion depth is %d\n", log_grp->rec_depth);
		print_pipe_group(log_grp->pipe_group);
		printf("\n");
		log_grp = log_grp->next;
	}
}

void print_check_int_list(t_int_list *list)
{
	printf("fd's are : ");
	while (list)
	{
		printf("%d, ", list->val);		
		list = list->next;
	}
	printf("\n");
}

void print_cmd(t_cmd_group *cmd_grp)
{
	printf("\n\t*command groups incoming*\n\n");
	print_check_int_list(cmd_grp->in);
	print_check_int_list(cmd_grp->out);
	printf("\nlimit is : %s\nargs are : ", cmd_grp->limit);
	mx_print_strarr(cmd_grp->args, " ");
	fprintf(stderr, "\n");
}
