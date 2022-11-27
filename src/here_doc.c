/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:15:33 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/26 16:06:01 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	exists(const char *fname)
{
	int	file;

	file = open(fname, O_RDONLY);
	if (file)
	{
		close(file);
		return (1);
	}
	return (0);
}

void	sub_fill_heredoc(int fd, char *limit)
{
	char	*line;
	char	*ret1;
	char	*ret2;

	ret1 = NULL;
	ret2 = NULL;
	while (1)
	{
		heredoc_sig();
		line = readline("here_doc> ");
		if (ft_strcmp(line, limit) == 0)
		{
			write(fd, ret1, ft_strlen(ret1));
			free(ret1);
			free(line);
			close(fd);
			exit(1);
		}
		ret2 = ft_strjoin(ret1, line);
		free(ret1);
		ret1 = ft_strjoin(ret2, "\n");
		free(ret2);
		free(line);
	}
}

void	fill_here_doc(int fd, char *limit)
{
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		sub_fill_heredoc(fd, limit);
	}
	else
		waitpid(pid, NULL, 0);
	signals();
}
