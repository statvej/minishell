/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:32:40 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/25 16:43:58 by fstaryk          ###   ########.fr       */
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

void	init_index(int *index)
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
