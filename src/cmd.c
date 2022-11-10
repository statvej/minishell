/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:33:45 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/10 16:31:43 by fstaryk          ###   ########.fr       */
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
			|| temp->type == OUTPUT_OVER || temp->type == HERE_DOC)
		{
			if(temp->next && (temp->next->type == TEXT || temp->next->type == EXTENDED))
			{
				fd = redirect(temp->type, temp->next->tok, temp->next->len, &pipe->cmd_group);
				temp->next->type = REDIRECTIONS;
				if (fd < 0)
					return (-1);
			}
			else if(temp->next && temp->next->next && (temp->next->next->type == TEXT \
				|| temp->next->next->type == EXTENDED))
			{
				fd = redirect(temp->type, temp->next->next->tok, temp->next->next->len, &pipe->cmd_group);
				temp->next->next->type = REDIRECTIONS;
				if (fd < 0)
					return (-1);
			}
			else
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

int redirect(int type, char *file, int len, t_cmd_group **cmds)
{
	int	fd;
	char *str;
	
	fd = -1;
	str = ft_strndup(file, len);
	printf("%s\n", str);
	if (type == INPUT)
	{
		fd = open(str, O_RDONLY);
		add_to_int_list(&(*cmds)->in, create_int_link(fd));
	}
	else if (type == OUTPUT_OVER)
	{
		fd = open(str, O_TRUNC | O_RDWR | O_CREAT, 0777);
		add_to_int_list(&(*cmds)->out, create_int_link(fd));
	}
	else if (type == OUTPUT_APPEND)
	{
		fd = open(str, O_APPEND | O_RDWR | O_CREAT, 0777);
		add_to_int_list(&(*cmds)->out, create_int_link(fd));
	}
	else if (type == HERE_DOC)
	{
		if((*cmds)->limit)
			free((*cmds)->limit);
		(*cmds)->limit = ft_strndup(str, len);
		fd = 1;
	}
	if (fd < 0)
		perror("ERROR WITH REDIRECTIONS");
	free(str);
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
        if(list_temp->type == TEXT || list_temp->type == EXTENDED)
            ac++;
        list_temp = list_temp->next;
        i++;
    }
    return ac;
}

int create_args(t_pipe_group *pipe)
{
    int ac;
    int i;
    int count;
    t_token_list *list_temp;

    i = 0;
    count = 0;
    list_temp = pipe->tok_list;
    ac = count_args(list_temp, pipe->tok_len);
	if(ac == 0)
		return -1;
	// printf("arg count is %d\n", ac);
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
	return 1;
}

t_cmd_group *create_cmdgrp(void)
{
    t_cmd_group *ret;

    ret = (t_cmd_group *)malloc(sizeof(t_cmd_group));
    ret->args = NULL;
    ret->in = NULL;
    ret->out = NULL;
	ret->pipes[0] = -1;
	ret->pipes[1] = -1;
	ret->child = -1;
	ret->command = NULL;
    ret->pos_paths = NULL; 
    ret->limit = NULL;
    return ret;
}