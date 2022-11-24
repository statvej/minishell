/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:15:33 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/24 19:32:00 by fstaryk          ###   ########.fr       */
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

void	fill_here_doc(int fd, char *limit)
{
	char	*line;
	char	*ret1;
	char	*ret2;

	ret1 = NULL;
	ret2 = NULL;
	while (1)
	{
		line = readline("here_doc> ");
		if (ft_strcmp(line, limit) == 0)
		{
			write(fd, ret1, ft_strlen(ret1));
			free(ret1);
			free(line);
			close(fd);
			return ;
		}
		ret2 = ft_strjoin(ret1, line);
		free(ret1);
		ret1 = ft_strjoin(ret2, "\n");
		free(ret2);
		free(line);
	}
}
