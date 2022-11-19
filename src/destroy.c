/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:36:45 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/19 13:34:56 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void    free_strarr(char **strarr)
{
	int i;

	i = 0;
	if(!strarr)
		return;
	while(strarr[i] != NULL)
	{
		free(strarr[i]);
		i++;
	}
	free(strarr);
}

void free_tokens(t_token_list *tok)
{
	t_token_list *temp;

	if(!tok)
		return;
	temp = tok;
	while (tok)
	{
		tok = tok->next;
		free(temp);
		if(temp->type == EXTENDED)
			free(temp->tok);
		temp = tok;
	}
}

void free_int_list(t_int_list *list)
{
	t_int_list *temp;

	if(!list)
		return;
	temp = list;
	while (list)
	{
		list = list->next;
		if(temp->val > 2)
			close(temp->val);
		free(temp);
		temp = list;
	}
}

void free_pipe_grp_nolist(t_pipe_group *pipe_grp)
{
	t_pipe_group * temp;
	
	if(!pipe_grp)	
		return;
	temp = pipe_grp;
	while (pipe_grp)
	{
		pipe_grp = pipe_grp->next;
		if(temp->cmd_group->command)
			free(temp->cmd_group->command);
		if(temp->cmd_group->limit)
		{
			free(temp->cmd_group->limit);
			unlink(".here_doc.tmp");
		}
		if(temp->cmd_group->args)
			free_strarr(temp->cmd_group->args);
		free_int_list(temp->cmd_group->in);
		free_int_list(temp->cmd_group->out);
		free(temp->cmd_group);
		free(temp);
		temp = pipe_grp;
	}
	
}

void free_data_in_loop(t_data *data)
{
	t_log_group *log_temp;
	t_log_group *log_free;

	if(data->pos_paths)
    	free_strarr(data->pos_paths);
	if(data->log_grp)
		free_tokens(data->log_grp->tok_list);
	log_temp = data->log_grp;
	log_free = log_temp;	
	while (log_temp)
	{
		log_temp = log_temp->next;
		free_pipe_grp_nolist(log_free->pipe_group);
		free(log_free);
		log_free = log_temp;
	}
	free(data);
}


// void free_data(t_data *data)
// {
// 	t_command *temp1;
// 	t_command *temp2;
// 	//free_strarr(data->envp);
// 	if(!data->cmds)
// 		return;
// 	if(!data->cmds->next)
// 		return;
// 	temp1 = data->cmds;
// 	while (temp1)
// 	{
// 		temp2 = temp1->next;
// 		free(temp1);
// 		temp1 = temp2;
// 	}
// }
