/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yarutiun <yarutiun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:53:45 by fstaryk           #+#    #+#             */
/*   Updated: 2022/12/02 11:27:07 by yarutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void mx_print_strarr(char **arr, const char *delim){
	if(!arr || !delim){
		return;
	}
	int i = 0;

	for(; arr[i]; i++){
		fprintf(stderr, "%s%s", arr[i], delim);
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

void print_ntoken(t_token_list *token, int n, char *depth)
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
	fprintf(stderr, "\n\tpipe groups incoming\n\n");
	while (pipe_grp)
	{
		fprintf(stderr, "pipe link #%d\n", i);
		print_ntoken(pipe_grp->tok_list, pipe_grp->tok_len, "\t");
		print_cmd(pipe_grp->cmd_group);
		pipe_grp = pipe_grp->next;
		i++;
	}	
}

void print_logic_grp(t_log_group *log_grp)
{
	while (log_grp)
	{
		fprintf(stderr, "tokens in group %d\n", log_grp->tok_len);
		fprintf(stderr, "\n");
		fprintf(stderr, "group needs %d", log_grp->needs);
		fprintf(stderr, "\n");
		fprintf(stderr, "recursion depth is %d\n", log_grp->rec_depth);
		print_pipe_group(log_grp->pipe_group);
		fprintf(stderr, "\n");
		log_grp = log_grp->next;
	}
}

void print_check_int_list(t_int_list *list)
{
	fprintf(stderr, "fd's are : ");
	while (list)
	{
		fprintf(stderr, "%d, ", list->val);		
		list = list->next;
	}
	fprintf(stderr, "\n");
}

void print_check_str_list(t_str_list *list)
{
	int j;
	fprintf(stderr, "strings are : \n");
	while (list)
	{
		j = 0;
		while (j < list->len)
		{
			fprintf(stderr, "%c", list->str[j]);
			j++;
		}
		fprintf(stderr, "\nstrict is %d\n", list->strict);		
		list = list->next;
	}
	fprintf(stderr, "\n");
}


void print_cmd(t_cmd_group *cmd_grp)
{
	fprintf(stderr, "\n\t*command groups incoming*\n\n");
	print_check_int_list(cmd_grp->in);
	print_check_int_list(cmd_grp->out);
	fprintf(stderr, "\nlimit is : %s\nargs are : ", cmd_grp->limit);
	mx_print_strarr(cmd_grp->args, " ");
	fprintf(stderr, "\n");
}

void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;
    
    for (i = size-1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            fprintf(stderr, "%u", byte);
        }
    }
    puts("");
}
