/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:35:57 by fstaryk           #+#    #+#             */
/*   Updated: 2022/10/17 15:03:37 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


t_token_list *create_token(int length, char *start, int type)
{
	t_token_list *token;
	token = (t_token_list*)malloc(sizeof(t_token_list));
// ft_strtrim(start, "\"\'");
	token->len = length;
	token->next = NULL;
	token->prev = NULL;
	token->tok = start;
	token->type = type;
	return token;
}

void add_token(t_token_list **first, t_token_list * to_add)
{
	t_token_list *temp;

	if(!to_add)
	{
		perror("sho? ti sho tworish");	
		return;
	}
	if(!(*first))
	{
		*first = to_add;
		return;
	}
	temp = *first;
	while (temp->next)
		temp = temp->next;
	temp->next = to_add;
	to_add->prev = temp;
}

t_token_list *token_delim_logic(t_token_list **global, int *len, int *needs)
{
	t_token_list *temp;
	temp = *global;
	int i;

	i = 0;
	if((*global)->next == NULL)
		return NULL;
	if ((*global)->prev == NULL)
		*needs = -1;
	else if((*global)->prev->type == LOGICAL_AND)
		*needs = 1;
	else if((*global)->prev->type == LOGICAL_OR)
		*needs = 0;
	while((*global)->type != LOGICAL_OR && (*global)->type != LOGICAL_AND)
	{
		if ((*global)->next == NULL)
		{
			i++;
			*len = i;
			return temp;
		}
		i++;
		*global = (*global)->next;
	}
	*len = i;
	if(!(*global)->next)
		{
			perror ("syntax error");
			return 0;
		}
	*global = (*global)->next;
	return temp;
}
//Before pipe it leaves one extra space
t_token_list *token_delim_pipe(t_token_list *global, int log_len, int *pipe_len)
{
	static int count;
	int i;
	t_token_list *ret;


	static t_token_list *save;
	if(save != global){
		save = global;
		print_ntoken(save, log_len, "\t\t\t");
		printf("\n\n");
	}

	
	if (count >= log_len - 1)
	{
		count = 0;
		return NULL;
	}
	i = 0;
	while (i < count)
	{
		i++;
		global = global->next;
	}
	ret = global;
	i = 0;
	while (global->type != PIPE)
	{
		if(count >= log_len - 1)
			return ret;
		global = global->next;
		i++;
		count++;
	}
	count++;
	*pipe_len = --i;
	return ret;
}

void restore_tok_list(t_token_list **global)
{
	while ((*global)->prev)
		(*global) = (*global)->prev;
}
