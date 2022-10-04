/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:35:57 by fstaryk           #+#    #+#             */
/*   Updated: 2022/10/04 17:56:57 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// t_data initData(char **envp)
// {
// 	t_data data;


// }

t_command *create_command(char **path, char *args, t_data *data)
{
	t_command *command;

	command = (t_command *)malloc(sizeof(t_command) * 1);
	command->args = args;
	command->path = path;
	command->next = NULL;
	command->data = data;
	return (command);
}

void add_command(t_command **first, t_command *second)
{
	(*first)->next = second;
	second->next = NULL; 
}
