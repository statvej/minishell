/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:50:03 by fstaryk           #+#    #+#             */
/*   Updated: 2022/10/10 18:41:54 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int is_space(char c)
{
	if (c== ' ' || (c >= 8 && c <= 14))
		return 1;
	else   
		return 0;
}

int get_type(char input){
	if (input == ' ' || (input >= 8 && input <= 14))
		return SPACE;
	if(input == '\'')
		return SING_QUOTES;
	if (input == '\"')
		return DUP_QUOTES;
	if (input == '|' || input == '>' || input == '<' || \
		 input == '&' || input == '(' || input == ')')
		return SEPARATOR;
	return TEXT;
}



//returns i counter for lexer func
int add_quot_tok(t_token_list **token, char *input, char **start, int *type)
{
	int i;

	i = 1;
	while(input[0] != input[i])
	{
		if (input[i] == '\0')
		{
			perror("quotes are not closed");
			return -1;
		}
		i++;
	}
	//printf("input is\t%s\nstart is\t%s\n", input, *start);
	add_token(token, create_token((int)(&input[i] - *start - 1), *start + 1, *type));
	*start = &input[i] + 1;
	*type = get_type(input[i + 1]);
	//printf("it gets type from %c\nretturns %d\n", input[i + 1], i);
	return (i);
}

void add_common_tok(t_token_list **token, char *in, char **start, int *type)
{
	add_token(token, create_token((int)(in - *start), *start, *type));
	*start = in;
	// fprintf(stderr, "%c\n", *in);
	*type = get_type(*in);
}

t_token_list *lexer(char *input)
{
	int i;
	int type;
	char *start;
	int ret;
	t_token_list *tokens;

	if (!input)
		return NULL;
	i = 0;
	tokens = NULL;
	type = get_type(input[i]);
	start = input;
	while(input[i])
	{	
		// printf("current is %c\n", input[i]);
		if (get_type(input[i]) == DUP_QUOTES || get_type(input[i]) == SING_QUOTES){
			add_common_tok(&tokens, &input[i], &start, &type);
			ret = add_quot_tok(&tokens, &input[i], &start, &type);
			if(ret == -1)
				return NULL;
			i += ret;
		}
		else if(type == SPACE && get_type(input[i]) != SPACE)
			add_common_tok(&tokens, &input[i], &start, &type);
		else if(type == TEXT && get_type(input[i]) != TEXT)
			add_common_tok(&tokens, &input[i], &start, &type);
		else if(type == SEPARATOR && get_type(input[i]) != SEPARATOR)
			add_common_tok(&tokens, &input[i], &start, &type);
		i++;
	}
	add_token(&tokens, create_token((int)(&input[i] - start), start, type));
	return tokens;
}
