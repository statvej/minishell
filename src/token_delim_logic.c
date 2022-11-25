/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_delim_logic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:14:07 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/25 15:23:34 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_cases_logic(int *count, int *len, int *needs, t_token_list *global)
{
	if (!len && !needs)
	{
		*count = 0;
		return (0);
	}
	if (!global)
		return (0);
	return (1);
}

void	sub_token_delim_logic(t_token_list *global, int *needs, int *i)
{
	if (global->prev == NULL)
		*needs = -1;
	else if (global->prev->type == LOGICAL_AND)
		*needs = 1;
	else if (global->prev->type == LOGICAL_OR)
		*needs = 0;
	*i = 1;
}

t_token_list	*token_delim_logic(t_token_list *global, int *len, int *needs)
{
	static int		count;
	int				i;
	t_token_list	*ret;

	if (!check_cases_logic(&count, len, needs, global))
		return (0);
	i = 0;
	while (global && i < count)
	{
		i++;
		global = global->next;
	}
	if (!global)
		return (NULL);
	ret = global;
	sub_token_delim_logic(global, needs, &i);
	while (global && !is_log_group(global))
	{
		global = global->next;
		i++;
		count++;
	}
	count++;
	*len = --i;
	return (ret);
}
