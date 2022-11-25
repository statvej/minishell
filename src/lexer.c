/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:50:03 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/25 16:43:52 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	sub_extend_token_types(char **separs, int *index, t_token_list *temp)
{
	int	i;

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
	return (1);
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
			if (!sub_extend_token_types(separs, index, temp))
				return (-1);
		temp = temp->next;
	}	
	return (1);
}

void	sub_lexer(int *type, char *input_i, char **start, t_token_list **tokens)
{
	if (*type == SPACE && get_type(*input_i) != SPACE)
		add_common_tok(tokens, input_i, start, type);
	else if (*type == TEXT && get_type(*input_i) != TEXT)
		add_common_tok(tokens, input_i, start, type);
	else if (*type == SEPAR_LESS && get_type(*input_i) != SEPAR_LESS)
		add_common_tok(tokens, input_i, start, type);
	else if (*type == SEPAR_MORE && get_type(*input_i) != SEPAR_MORE)
		add_common_tok(tokens, input_i, start, type);
	else if (*type == SEPAR_PIPE && get_type(*input_i) != SEPAR_PIPE)
		add_common_tok(tokens, input_i, start, type);
	else if (*type == PRNTH_LEFT)
		add_common_tok(tokens, input_i, start, type);
	else if (*type == PRNTH_RIGHT)
		add_common_tok(tokens, input_i, start, type);
	else if (*type == LOGICAL_AND && get_type(*input_i) != LOGICAL_AND)
		add_common_tok(tokens, input_i, start, type);
}

int	sub_lexer_quotes(int *type, char *input_i, \
					char **start, t_token_list **tokens)
{
	int	ret;

	ret = 0;
	if (get_type(*input_i) == DUP_QUOTES || \
					get_type(*input_i) == SING_QUOTES)
	{
		if (!(*tokens))
			add_common_tok(tokens, input_i, start, type);
		ret = add_quot_tok(tokens, input_i, start, type);
		if (ret == -1)
		{
			free_tokens(*tokens);
			return (0);
		}
	}
	return (ret);
}

t_token_list	*lexer(char *input)
{
	int				i;
	int				type;
	char			*start;
	t_token_list	*tokens;

	if (!input)
		return (NULL);
	i = 0;
	tokens = NULL;
	type = get_type(input[i]);
	start = input;
	while (input[i])
	{	
		sub_lexer(&type, &input[i], &start, &tokens);
		i += sub_lexer_quotes(&type, &input[i], &start, &tokens) + 1;
	}
	add_token(&tokens, create_token((int)(&input[i] - start), start, type));
	if (extend_token_types(&tokens) == -1)
		return (free_tokens(tokens));
	return (tokens);
}
