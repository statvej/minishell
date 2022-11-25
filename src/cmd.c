/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchuk <gpinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:33:45 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/25 15:00:19 by gpinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	sub_open_redir(t_token_list *temp, t_pipe_group *pipe)
{
	int	fd;

	if (temp->next && (temp->next->type == TEXT || \
		temp->next->type == EXTENDED))
	{
		fd = redirect(temp->type, temp->next->tok, \
		temp->next->len, &pipe->cmd_group);
		temp->next->type = REDIRECTIONS;
		if (fd < 0)
			return (-1);
	}
	else if (temp->next && temp->next->next && \
		(temp->next->next->type == TEXT || \
		temp->next->next->type == EXTENDED))
	{
		fd = redirect(temp->type, temp->next->next->tok, \
		temp->next->next->len, &pipe->cmd_group);
		temp->next->next->type = REDIRECTIONS;
		if (fd < 0)
			return (-1);
	}
	return (1);
}

int	open_redir(t_pipe_group *pipe)
{
	t_token_list	*temp;
	int				i;
	int				fd;

	temp = pipe->tok_list;
	i = 0;
	pipe->cmd_group = create_cmdgrp();
	while (temp && i < pipe->tok_len)
	{
		if (temp->type == INPUT || temp->type == OUTPUT_APPEND \
			|| temp->type == OUTPUT_OVER || temp->type == HERE_DOC)
		{
			fd = sub_open_redir(temp, pipe);
			if (fd == -1)
			{
				perror("ERROR WITH REDIRECTIONSSSSSS");
				return (-1);
			}
		}
		i++;
		temp = temp->next;
	}
	return (1);
}

int	count_args(t_token_list *list, int list_len)
{
	t_token_list	*list_temp;
	int				i;
	int				ac;

	ac = 0;
	i = 0;
	list_temp = list;
	while (list_temp && i < list_len)
	{
		if (list_temp->type == TEXT || list_temp->type == EXTENDED)
			ac++;
		list_temp = list_temp->next;
		i++;
	}
	return (ac);
}

int	create_args(t_pipe_group *pipe)
{
	int				ac;
	int				i;
	int				count;
	t_token_list	*list_temp;

	i = 0;
	count = 0;
	list_temp = pipe->tok_list;
	ac = count_args(list_temp, pipe->tok_len);
	if (ac == 0)
		return (-1);
	pipe->cmd_group->args = (char **)malloc(sizeof(char *) * (ac + 1));
	while (list_temp && i < pipe->tok_len)
	{
		if (list_temp->type == TEXT || list_temp->type == EXTENDED)
		{
			pipe->cmd_group->args[count] = ft_strndup(list_temp->tok, \
			list_temp->len);
			count++;
		}
		list_temp = list_temp->next;
		i++;
	}
	pipe->cmd_group->args[ac] = NULL;
	return (1);
}

t_cmd_group	*create_cmdgrp(void)
{
	t_cmd_group	*ret;

	ret = (t_cmd_group *)malloc(sizeof(t_cmd_group));
	ret->args = NULL;
	ret->in = NULL;
	ret->out = NULL;
	ret->command = NULL;
	ret->limit = NULL;
	return (ret);
}
