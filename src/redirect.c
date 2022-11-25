/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchuk <gpinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:59:55 by gpinchuk          #+#    #+#             */
/*   Updated: 2022/11/25 15:00:38 by gpinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h" 

int	fd_opener(int type, t_cmd_group **cmds, char *str)
{
	int	fd;

	fd = -1;
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
	return (fd);
}

int	redirect(int type, char *file, int len, t_cmd_group **cmds)
{
	int		fd;
	char	*str;

	fd = -1;
	str = ft_strndup(file, len);
	if (type == INPUT || type == OUTPUT_OVER || type == OUTPUT_APPEND)
		fd = fd_opener(type, cmds, str);
	else if (type == HERE_DOC)
	{
		fd = open(".here_doc.tmp", O_WRONLY | O_CREAT, 0777);
		if ((*cmds)->limit)
			free((*cmds)->limit);
		(*cmds)->limit = ft_strndup(str, len);
		fill_here_doc(fd, (*cmds)->limit);
		fd = open(".here_doc.tmp", O_RDONLY);
		add_to_int_list(&(*cmds)->in, create_int_link(fd));
	}
	if (fd < 0)
		perror("ERROR WITH REDIRECTIONS");
	free(str);
	return (fd);
}
