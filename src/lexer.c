/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:50:03 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/24 19:47:27 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_separs(char **separs)
{
	separs[0] = ">";
	separs[1] = "<";
	separs[2] = ">>";
	separs[3] = "<<";
	separs[4] = "|";
	separs[5] = "(";
	separs[6] = ")";
	separs[7] = "&&";
	separs[8] = "||";
}

void init_index(int *index)
{
	index[0] = OUTPUT_OVER;
	index[1] = INPUT;
	index[2] = OUTPUT_APPEND;
	index[3] = HERE_DOC;
	index[4] = PIPE;
	index[5] = PRNTH_LEFT;
	index[6] = PRNTH_RIGHT;
	index[7] = LOGICAL_AND;
	index[8] = LOGICAL_OR;
}

int	extend_token_types(t_token_list **token)
{
	int				i;
	t_token_list	*temp;
	char			*separs[9];
	int				index[9];

	init_separs(separs);
	init_index(index);
	i = 0;
	temp = *token;
	while (temp)
	{
		if (temp->type == PRNTH_RIGHT || temp->type == SEPAR_MORE || \
				temp->type == SEPAR_PIPE || temp->type == LOGICAL_AND || \
						temp->type == PRNTH_LEFT || temp->type == SEPAR_LESS)
		{
			i = 0;
			while (separs[i])
			{
				if (i == 9)
				{
					perror("unknown separator");
					return (-1);
				}
				if (ft_strncmp(separs[i], temp->tok, temp->len) == 0)
				{
					temp->type = index[i];
					break ;
				}
				i++;
			}
		}
		temp = temp->next;
	}	
	return (1);
}

int	get_type(char input)
{
	if (input == ' ' || (input >= 8 && input <= 14))
		return (SPACE);
	if (input == '\'')
		return (SING_QUOTES);
	if (input == '\"')
		return (DUP_QUOTES);
	if (input == '|')
		return (SEPAR_PIPE);
	if (input == '>')
		return (SEPAR_MORE);
	if (input == '<')
		return (SEPAR_LESS);
	if (input == '&')
		return (LOGICAL_AND);
	if (input == '(')
		return (PRNTH_LEFT);
	if (input == ')')
		return (PRNTH_RIGHT);
	return (TEXT);
}

//returns i counter for lexer func
int	add_quot_tok(t_token_list **token, char *input, char **start, int *type)
{
	int	i;

	i = 1;
	while (input[0] != input[i])
	{
		if (input[i] == '\0')
		{
			perror("quotes are not closed");
			return (-1);
		}
		i++;
	}
	if (i == 1)
		add_token(token, create_token(0, *start, *type));
	else
		add_token(token, create_token(i - 1, *start + 1, *type));
	*start = &input[i] + 1;
	*type = get_type(input[i + 1]);
	return (i);
}

void	add_common_tok(t_token_list **token, char *in, char **start, int *type)
{
	add_token(token, create_token((int)(in - *start), *start, *type));
	*start = in;
	*type = get_type(*in);
}

t_token_list	*lexer(char *input)
{
	int				i;
	int				type;
	char			*start;
	int				ret;
	t_token_list	*tokens;

	if (!input)
		return (NULL);
	i = 0;
	tokens = NULL;
	type = get_type(input[i]);
	start = input;
	while (input[i])
	{	
		if (type == SPACE && get_type(input[i]) != SPACE)
			add_common_tok(&tokens, &input[i], &start, &type);
		else if (type == TEXT && get_type(input[i]) != TEXT)
			add_common_tok(&tokens, &input[i], &start, &type);
		else if (type == SEPAR_LESS && get_type(input[i]) != SEPAR_LESS)
			add_common_tok(&tokens, &input[i], &start, &type);
		else if (type == SEPAR_MORE && get_type(input[i]) != SEPAR_MORE)
			add_common_tok(&tokens, &input[i], &start, &type);
		else if (type == SEPAR_PIPE && get_type(input[i]) != SEPAR_PIPE)
			add_common_tok(&tokens, &input[i], &start, &type);
		else if (type == PRNTH_LEFT)
			add_common_tok(&tokens, &input[i], &start, &type);
		else if (type == PRNTH_RIGHT)
			add_common_tok(&tokens, &input[i], &start, &type);
		else if (type == LOGICAL_AND && get_type(input[i]) != LOGICAL_AND)
			add_common_tok(&tokens, &input[i], &start, &type);
		if (get_type(input[i]) == DUP_QUOTES || \
					get_type(input[i]) == SING_QUOTES)
		{
			if (!tokens)
				add_common_tok(&tokens, &input[i], &start, &type);
			ret = add_quot_tok(&tokens, &input[i], &start, &type);
			if (ret == -1)
			{
				free_tokens(tokens);
				return (NULL);
			}
			i += ret;
		}
		i++;
	}
	add_token(&tokens, create_token((int)(&input[i] - start), start, type));
	if (extend_token_types(&tokens) == -1)
	{
		free_tokens(tokens);
		return (NULL);
	}
	return (tokens);
}
