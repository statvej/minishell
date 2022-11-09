/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:33:45 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/09 18:44:04 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int open_redir(t_pipe_group *pipe)
{
	t_token_list *temp;
	int i;
	int fd;

	temp = pipe->tok_list;
	i = 0;
	pipe->cmd_group = create_cmdgrp();
	while (i < pipe->tok_len)
	{
		if(temp->type == INPUT || temp->type == OUTPUT_APPEND \
			|| temp->type == OUTPUT_OVER || temp->type == HERE_DOC) //not sure about here_doc
		{
			if(temp->next && (temp->next->type == TEXT || temp->next->type == EXTENDED))
			{
				fd = redirect(temp->type, temp->next->tok, &pipe->cmd_group);
				temp->next->type = REDIRECTIONS;
				if (fd < 0)
					return (-1);
			}
			else if(temp->next->next && (temp->next->next->type == TEXT \
				|| temp->next->next->type == EXTENDED))
			{
				fd = redirect(temp->type, temp->next->next->tok, &pipe->cmd_group);
				temp->next->next->type = REDIRECTIONS;
				if (fd < 0)
					return (-1);
			}
			else
			{
				perror("ERROR WITH REDIRECTIONS");
				return (-1);	
			}
		}
		i++;
		temp = temp->next;
	}
	return (1);
}

int redirect(int type, char *file, t_cmd_group **cmds)
{
	int	fd;

	fd = -1;
	if (type == INPUT)
	{
		fd = open(file, O_RDONLY);
		add_to_int_list(&(*cmds)->in, create_int_link(fd));
	}
	else if (type == OUTPUT_OVER)
	{
		fd = open(file, O_TRUNC | O_RDWR | O_CREAT, 0777);
		add_to_int_list(&(*cmds)->out, create_int_link(fd));
	}
	else if (type == OUTPUT_APPEND)
	{
		fd = open(file, O_APPEND | O_RDWR | O_CREAT, 0777);
		add_to_int_list(&(*cmds)->out, create_int_link(fd));
	}
	if (fd < 0)
		perror("ERROR WITH REDIRECTIONS");
	return (fd);
}

int count_args(t_token_list *list, int list_len){
    t_token_list *list_temp;
    int i;
    int ac;
    
    ac = 0;
    i = 0;
    list_temp = list;
    while (i < list_len)
    {
        if(list_temp == TEXT)
            ac++;
        list_temp = list_temp->next;
        i++;
    }
    return ac;
}

void create_args(t_pipe_group *pipe)
{
    int ac;
    int i;
    int count;
    t_token_list *list_temp;

    i = 0;
    count = 0;
    list_temp = pipe->tok_list;
    ac = count_args(list_temp, pipe->tok_len);
    pipe->cmd_group->args = (char **)malloc(sizeof(char *) * (ac + 1));
    while (i < pipe->tok_len)
    {
        if(list_temp->type == TEXT || list_temp->type == EXTENDED)
        {
            pipe->cmd_group->args[count] = ft_strndup(list_temp->tok, list_temp->len);
            count++; 
        }
        list_temp = list_temp->next;
        i++;
    }
    pipe->cmd_group->args[ac] = NULL;
}

t_cmd_group *create_cmdgrp(void)
{
    t_cmd_group *ret;

    ret = (t_cmd_group *)malloc(sizeof(t_cmd_group));
    ret->args = NULL;
    ret->in = NULL;
    ret->out = NULL;
    ret->pos_paths = NULL; 
    ret->here_doc = 0;
    return ret;
}