/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_delim_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:21:49 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/25 15:25:35 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_count_delim_pipe(int *count, int log_len, int *i)
{
	if (*count >= log_len)
	{
		*count = 0;
		return (0);
	}
	else if (*count <= 1)
		*count = 1;
	*i = 1;
	return (1);
}

t_token_list	*token_delim_pipe(t_token_list *global, \
									int log_len, int *pipe_len)
{
	static int		count;
	int				i;
	t_token_list	*ret;

	if (!global)
		return (NULL);
	i = 1;
	global = skip_n_token(global, count);
	ret = global;
	if (!check_count_delim_pipe(&count, log_len, &i))
		return (NULL);
	while (global->type != PIPE)
	{
		global = global->next;
		i++;
		count++;
		if (count >= log_len)
		{
			*pipe_len = i;
			return (ret);
		}
	}
	count++;
	*pipe_len = --i;
	return (ret);
}
