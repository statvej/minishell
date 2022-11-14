#include "minishell.h"



t_pipe_group *create_pipe_link(t_token_list *tok_list, int tok_len)
{
	t_pipe_group *pipe_grp;

	pipe_grp = (t_pipe_group *)malloc(sizeof(t_pipe_group));
	pipe_grp->tok_list = tok_list;
	pipe_grp->tok_len = tok_len;
	pipe_grp->next = NULL;
	pipe_grp->prev = NULL;
    pipe_grp->cmd_group = NULL;

	return (pipe_grp);
}

void add_pipe_link(t_pipe_group **first, t_pipe_group *to_add)
{
	t_pipe_group *temp;

	if (!to_add)
		return;
	if(!(*first))
	{
		*first = to_add;
		return ;
	}
	temp = *first;
	while (temp->next)
		temp = temp->next;
	temp->next = to_add;
	to_add->prev = temp;
}

void create_pipe_group(t_log_group *log_grp)
{
	t_token_list *temp;
	int len;
	int i=0;

	if(!log_grp)
		return ;
	while (log_grp)
	{
		temp = token_delim_pipe(log_grp->tok_list, log_grp->tok_len, &len);
		// print_ntoken(temp, len);
		while(temp)
		{
			add_pipe_link(&log_grp->pipe_group, create_pipe_link(temp, len));		
			temp = token_delim_pipe(log_grp->tok_list, log_grp->tok_len, &len);
			i++;
			// print_ntoken(temp, len);
		}
		log_grp = log_grp->next;
	}
}