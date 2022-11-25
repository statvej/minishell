/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_errors_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:05:15 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/25 17:41:32 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	cancel_prnth_loc(int *l, int *o, int *p)
{
	if (p)
		*p = 0;
	if (o)
		*o = 0;
	if (l)
		*l = 0;
}

void	prnth_loc_if_state(t_token_list *l, int *on_the_prnth, \
	int *log_in_power, int *prnth_valid)
{
	if (!is_prnth(l) && l->type != SPACE)
		*log_in_power = 0;
	if (is_prnth(l))
		*on_the_prnth = 1;
	if (is_log_group(l))
		*log_in_power = 1;
	if (*log_in_power && *on_the_prnth)
		*prnth_valid = 1;
}

int	check_prnth_location(t_token_list *l)
{
	int	log_in_power;
	int	on_the_prnth;
	int	prnth_valid;

	if (is_prnth(l) || (l->type == SPACE && l->next && is_prnth(l->next)))
		log_in_power = 1;
	on_the_prnth = 0;
	prnth_valid = 0;
	while (l)
	{
		prnth_loc_if_state(l, &on_the_prnth, &log_in_power, &prnth_valid);
		if (on_the_prnth && !is_prnth(l) && l->type != SPACE && \
														!is_log_group(l))
		{
			if (prnth_valid)
				cancel_prnth_loc(&log_in_power, &on_the_prnth, &prnth_valid);
			else
				return (-1);
		}	
		l = l->next;
	}
	return (0);
}
