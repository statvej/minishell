/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extention_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:18:13 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/16 14:38:06 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../inc/minishell.h"

char *sub_extend(char *var, int len, char **env)
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
	while (env[i])
	{
		if (ft_strncmp(var, env[i], var_len) == 0)
		{
			return ft_strdup(&env[i][var_len + 1]);
		}
		i++;
	}
	return NULL;
}

char	*extend(char *var, int len, char **env)
{
	char *ext;
	char *ret;
	int i;

	i = 0;
	ret = NULL;
	while (i < len)
	{
		if(var[i] == '$')
		{
			ext = sub_extend(&var[i + 1], len - i - 1, env);
			ret = ft_strnnjoin(ret, ft_strlen(ret), ext, ft_strlen(ext));
		}
		i++;
	}
	return ret;
	
}

//need to add $?
void open_extentions(t_token_list **tok_list, int tok_len, char **env)
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
				ext = extend(&temp->tok[i], temp->len - i, env);			
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


