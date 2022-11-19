/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 14:46:30 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/19 14:46:41 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int is_group(t_token_list *list)
{
	if(list->type == PIPE || list->type == LOGICAL_AND ||
		 list->type == LOGICAL_OR)
		return 1;
	else
		return 0;
}

int is_log_group(t_token_list *list)
{
	if(list->type == LOGICAL_AND || list->type == LOGICAL_OR)
		return 1;
	else
		return 0;
}

int is_prnth(t_token_list *list)
{
	if(list->type == PRNTH_RIGHT || list->type == PRNTH_LEFT)
		return 1;
	else
		return 0;
}

int is_redir(t_token_list *list)
{
	if(list->type == OUTPUT_APPEND || list->type == OUTPUT_OVER ||
		 list->type == INPUT || list->type == HERE_DOC)
		return 1;
	else
		return 0;
}