/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:50:03 by fstaryk           #+#    #+#             */
/*   Updated: 2022/10/12 17:26:06 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int extend_token_types(t_token_list **token)
{
	int i;
	t_token_list *temp;
	char *separs[] = { ">" ,     "<",    ">>"      ,    "<<"   ,  "|"   , "(",         ")",        "&&"  ,       "||"};
	int index[] = {OUTPUT_OVER, INPUT ,OUTPUT_APPEND, HERE_DOC, PIPE, PRNTH_LEFT, PRNTH_RIGHT, LOGICAL_AND, LOGICAL_OR};

	i = 0;
	temp = *token;
	while (temp)
	{
		if(temp->type == PRNTH_RIGHT || temp->type == SEPAR_MORE ||\
				temp->type == SEPAR_PIPE || temp->type == LOGICAL_AND ||\
					 temp->type == PRNTH_LEFT)
		{
			i = 0;
	
			while (separs[i])
			{
				if(i == 9)
				{
					perror("unknown separator");
					return -1;	
				}
				if(ft_strncmp(separs[i], temp->tok, temp->len) == 0)
				{
					// printf("temptok %.2s and index is %d\n", temp->tok, index[i]);
					temp->type = index[i];		
					break;;
				}
				i++;
			}
		}
		temp = temp->next;
	}	
	return 1;
}


int get_type(char input){
	if (input == ' ' || (input >= 8 && input <= 14))
		return SPACE;
	if (input == '\'')
		return SING_QUOTES;
	if (input == '\"')
		return DUP_QUOTES;
	if (input == '|')
		return SEPAR_PIPE;
	if (input == '>')
		return SEPAR_MORE;
	if (input == '<')
		return SEPAR_MORE;
	if(input == '&')
		return LOGICAL_AND;
	if (input == '(')
		return PRNTH_LEFT;
	if (input == ')')
		return PRNTH_RIGHT;
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
		else if(type == SEPAR_LESS && get_type(input[i]) != SEPAR_LESS)
			add_common_tok(&tokens, &input[i], &start, &type);
		else if(type == SEPAR_MORE && get_type(input[i]) != SEPAR_MORE)
			add_common_tok(&tokens, &input[i], &start, &type);
		else if(type == SEPAR_PIPE && get_type(input[i]) != SEPAR_PIPE)
			add_common_tok(&tokens, &input[i], &start, &type);
		else if(type == PRNTH_LEFT && get_type(input[i]) != PRNTH_LEFT)
			add_common_tok(&tokens, &input[i], &start, &type);
		else if(type == PRNTH_RIGHT && get_type(input[i]) != PRNTH_RIGHT)
			add_common_tok(&tokens, &input[i], &start, &type);
		else if(type == LOGICAL_AND && get_type(input[i]) != LOGICAL_AND)
			add_common_tok(&tokens, &input[i], &start, &type);
		i++;
	}
	add_token(&tokens, create_token((int)(&input[i] - start), start, type));
	extend_token_types(&tokens);
	return tokens;
}

