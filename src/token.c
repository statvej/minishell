/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:35:57 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/19 17:40:41 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


t_token_list *create_token(int length, char *start, int type)
{
	t_token_list *token;

	if(!length && !(type == DUP_QUOTES || type == SING_QUOTES))
		return NULL;
	token = (t_token_list*)malloc(sizeof(t_token_list));
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

/* VERSION 1*/

// t_token_list *token_delim_logic(t_token_list **global, int *len, int *needs)
// {
// 	t_token_list *temp;
// 	temp = *global;
// 	int i;
// 	static int solo;

// 	i = 0;
// 	if(!global || solo == 1)
// 	{
// 		solo = 0;
// 		return NULL;
// 	}
// 	if((*global)->next == NULL && (*global)->prev == NULL)
// 	{
// 		*len = 1;
// 		*needs = -1;
// 		solo = 1;
// 		return temp;
// 	}
// 	// else if((*global)->next == NULL)
// 	// 	return NULL;
// 	if ((*global)->prev == NULL)
// 		*needs = -1;
// 	else if((*global)->prev->type == LOGICAL_AND)
// 		*needs = 1;
// 	else if((*global)->prev->type == LOGICAL_OR)
// 		*needs = 0;
// 	while((*global)->type != LOGICAL_OR && (*global)->type != LOGICAL_AND)
// 	{
// 		if ((*global)->next == NULL)
// 		{
// 			i++;
// 			*len = i;
// 			return temp;
// 		}
// 		i++;
// 		*global = (*global)->next;
// 	}
// 	*len = i;
// 	if(!(*global)->next)
// 		{
// 			perror ("syntax error");
// 			return 0;
// 		}
// 	*global = (*global)->next;
// 	return temp;
// }

/* VERSION 2*/

t_token_list *token_delim_logic(t_token_list *global, int *len, int *needs)
{
	static int count;
	int i;
	t_token_list *ret;
	
	if(!len && !needs)
	{
		count = 0;
		return NULL;
	}
	if(!global)
		return NULL;
	i = 0;
	//coming to the pointed from last itteration 
	while (global && i < count)
	{
		i++;
		global = global->next;
	}
	if(!global)
		return NULL;
	ret = global;
	if (global->prev == NULL)
		*needs = -1;
	else if(global->prev->type == LOGICAL_AND)
		*needs = 1;
	else if(global->prev->type == LOGICAL_OR)
		*needs = 0;
	i = 1;
	while (global && !is_log_group(global))
	{
		global = global->next;
		i++;
		count++;
	}
	//count ++ for junping over "|"
	count++;
	//--len for not counting "|" as we already encountered it
	*len = --i;
	return ret;
}

//Before pipe it leaves one extra space
t_token_list *token_delim_pipe(t_token_list *global, int log_len, int *pipe_len)
{
	static int count;
	int i;
	t_token_list *ret;

	if(!global)
		return NULL;
		
	i = 1;
	//coming to the pointed from last itteration 
	while (i < count)
	{
		i++;
		global = global->next;
	}
	ret = global;
	
	if (count >= log_len)
	{
		count = 0;
		return NULL;
	}
	else if(count <= 1)
		count = 1;
		
	i = 1;
	while (global->type != PIPE)
	{
		global = global->next;
		i++;
		count++;
		if(count >= log_len)
		{
			//for the end of log_group
			*pipe_len = i;
			return ret;
		}
	}
	//count ++ for junping over "|"
	count++;
	//--len for not counting "|" as we already encountered it
	*pipe_len = --i;
	return ret;
}

void restore_tok_list(t_token_list **global)
{
	while ((*global)->prev)
		(*global) = (*global)->prev;
}
