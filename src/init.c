/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:35:57 by fstaryk           #+#    #+#             */
/*   Updated: 2022/10/10 18:34:30 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_data *init_data(char **envp)
{
	t_data *data;

	data = (t_data *)malloc(sizeof(t_data));
	data->cmds = NULL;
	data->envp = envp;
	data->eout = STR_ERR;
	data->in = STR_IN;
	data->out = STR_OUT;
	return data;
}

t_command *create_command(char *path, char **args, t_data *data)
{
	t_command *command;

	command = (t_command *)malloc(sizeof(t_command));
	command->args = args;
	command->path = path;
	command->next = NULL;
	command->data = data;
	return (command);
}

void add_command(t_command **first, t_command *to_add)
{
	t_command *temp;

	if (!to_add)
		return;
	if(!(*first))
	{
		*first = to_add;
		return ;
	}
	temp = *first;
	while (temp->next)
		temp = temp->next;
	temp->next = to_add;
}

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