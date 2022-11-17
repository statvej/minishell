/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:42:39 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/17 14:41:24 by fstaryk          ###   ########.fr       */
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

// logic and pipe groups
int check_groups_pos_content(t_token_list *list)
{
	int looking_for_word;

	looking_for_word = 0;
	if(is_group(list))
		return -1;
	while (list)
	{
		if(is_group(list) && looking_for_word)
			return -1;
		if(looking_for_word && (list->type == TEXT || list->type == DUP_QUOTES || list->type == SING_QUOTES))
			looking_for_word = 0;
		if(is_group(list) && !looking_for_word)
			looking_for_word = 1;
		list = list->next;
	}
	if(looking_for_word)
		return -1;
	return 1;
}

// correct chars in special symbols
int check_tok_content(t_token_list *list)
{
	while (list)
	{
		if(list->type == PIPE && list->len != 1)
			return -1;
		if((list->type == LOGICAL_AND || list->type == LOGICAL_OR) && list->len != 2)
			return -1;
		if((list->type == OUTPUT_APPEND || list->type == HERE_DOC) && list->len != 2)
			return -1;
		if((list->type == OUTPUT_OVER || list->type == INPUT) && list->len != 1)
			return -1;	
		if(is_prnth(list) && is_prnth(list->next))
			return -1;
		list = list->next;
	}
	return 1;
}

// something after redirs 
int check_redir_dest(t_token_list *list)
{
	int looking_for_dest;
	
	looking_for_dest = 0;
	while(list)
	{
		if (is_redir(list) && !looking_for_dest)
			looking_for_dest = 1;
		if( (list->type == TEXT || list->type == DUP_QUOTES || list->type == SING_QUOTES) && looking_for_dest)
			looking_for_dest = 0;
		if(looking_for_dest && (is_redir(list) || is_group(list)))
			return -1;
		
		list = list->next;
	}
	return 1;
}

int check_prnth_location(t_token_list *list)
{
	int log_grp_in_power;
	int on_the_prnth;
	int prnth_valid;
	
	on_the_prnth = 0;
	//because we can have prnth at the begining
	if(is_prnth(list) || (list->type == SPACE && list->next && is_prnth(list->next)))
		log_grp_in_power = 1;
	prnth_valid = 0;
	while(list)
	{
		if(is_prnth(list))
			on_the_prnth = 1;
		if(is_log_group(list))
			log_grp_in_power = 1;
		if(log_grp_in_power && on_the_prnth)
			prnth_valid = 1;
		if(on_the_prnth && !is_prnth(list) && list->type != SPACE && !is_log_group(list))
		{
			if(prnth_valid)
			{
				prnth_valid = 0;
				on_the_prnth = 0;
				log_grp_in_power = 0;
			}
			else
				return -1;
		}	
		list = list->next;
	}
	return 0;
}


int	check_lexical_errors(t_token_list *list)
{
	if(check_groups_pos_content(list) == -1)
		return -1;
	if(check_tok_content(list) == -1)
		return -1;
	// if(check_redir_dest(list) == -1)
	// 	return -1;
	if(check_prnth_location(list) == -1)
		return -1;
	return 1;
}
