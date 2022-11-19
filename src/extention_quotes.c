/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extention_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:18:13 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/19 17:01:05 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../inc/minishell.h"

char *sub_extend(char *var, int len)
{
	int i;
	char *ret;
	int var_len;
	
	i = 0;
	var_len = 0;
	ret = NULL;
	while (var_len < len)
	{
		if(var[var_len] == '$')
			break;
		var_len++;
	}
	while (g_env[i])
	{
		if (ft_strncmp(var, g_env[i], var_len) == 0)
		{
			return ft_strdup(&g_env[i][var_len + 1]);
		}
		i++;
	}
	return NULL;
}



char	*extend(char *var, int len, int last_ret)
{
	char *ext;
	char *ret;
	char *to_free;
	int i;

	i = 0;
	ret = NULL;
	while (i < len)
	{
		if(var[i] == '$')
		{
			if(var[i + 1] == '?')
				ext = ft_itoa(last_ret);			
			else
				ext = sub_extend(&var[i + 1], len - i - 1);
			to_free = ret;
			ret = ft_strnnjoin(ret, ft_strlen(ret), ext, ft_strlen(ext));
			free(to_free);
			free(ext);
		}
		i++;
	}
	return ret;
}

//need to add $?
void open_extentions(t_token_list **tok_list, int tok_len, int last_ret)
{
	t_token_list *temp = *tok_list;
	int i;
	int count;
	char *ext;
	
	count = 0;
	while (temp && count < tok_len)
	{
		i = 0;
		while (i < temp->len && (temp->type == TEXT ||  temp->type == DUP_QUOTES || temp->type == EXTENDED))
		{
			if (temp->tok[i] == '$')
			{
				ext = extend(&temp->tok[i], temp->len - i, last_ret);			
				temp->tok = ft_strnnjoin(temp->tok, i, ext, ft_strlen(ext));
				temp->len = ft_strlen(temp->tok);
				if (temp->type == TEXT)
					temp->type = EXTENDED;
				if(ext)
					free(ext);
			}
			i++;
		}
		count++;
		temp = temp->next;
	}
}

void open_quotes(t_token_list **tok_list, int *tok_lenth)
{
	t_token_list *temp;
	t_token_list *start;
	int i;
	int j[2]= {0, 0};

	i = 0;
	temp = *tok_list;
	while (temp)
	{
		if(temp->type == DUP_QUOTES || temp->type == SING_QUOTES)
			{
				if(temp->prev && (temp->prev->type == TEXT || temp->prev->type == EXTENDED))
				{
					j[0] = i - 1;
					start = temp->prev;
				}
				else
				{
 					j[0] = i;
					start = temp;
				}
				if(temp->next && temp->next->len && (temp->next->type == TEXT || temp->next->type == EXTENDED))
				{
					j[1] = i + 1;
				}
				else 
					j[1] = i;
				strtoknjoin(&start, (j[1] - j[0]));
			}
		i++;
		temp = temp->next;
	}
	*tok_lenth -= (j[1] - j[0]);
}


