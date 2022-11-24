/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion_depth.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:54:03 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/24 19:11:16 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	get_max_depth(t_token_list *tok_list)
{
	int	openings;
	int	closings;

	openings = 0;
	closings = 0;
	while (tok_list)
	{
		if (tok_list->type == PRNTH_LEFT)
			openings++;
		if (tok_list->type == PRNTH_RIGHT)
			closings++;
		tok_list = tok_list->next;
	}
	//parenthesis not closed
	if (openings - closings != 0)
		return (-1);
	return (openings);
}

void	get_prnth_count(t_token_list *tok_list, int len, int *op, int *cl)
{
	int	openings;
	int	closings;
	int	i;

	i = 0;
	openings = 0;
	closings = 0;
	while (tok_list && i < len)
	{
		if (tok_list->type == PRNTH_LEFT)
			openings++;
		if (tok_list->type == PRNTH_RIGHT)
			closings++;
		tok_list = tok_list->next;
		i++;
	}
	*op = openings;
	*cl = closings;
}

//here depth is kinda reversed for purpose of using less variables
int	set_recursion_depth(t_log_group *log_grp)
{
	int	max_depth;
	int	cl;
	int	op;
	int	cur_depth;

	max_depth = get_max_depth(log_grp->tok_list);
	cur_depth = max_depth;
	if (max_depth == -1)
		return (-1);
	while (log_grp)
	{
		get_prnth_count(log_grp->tok_list, log_grp->tok_len, &op, &cl);
		cur_depth -= op;
		log_grp->rec_depth = max_depth - cur_depth;
		cur_depth += cl;
		log_grp = log_grp->next;
	}
	return (1);
}
