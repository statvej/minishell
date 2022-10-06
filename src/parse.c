/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:03:34 by fstaryk           #+#    #+#             */
/*   Updated: 2022/10/06 16:04:45 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// char    **connect_quotes(char **split)
// {
// 	int i;
// 	int fst;
// 	int lst;

// 	i = 0;
// 	fst = -1;
// 	lst = -1;
// 	while (split[i] != NULL)
// 	{
// 		if (ft_strchr(split[i], '"') && fst == -1)
// 		{
// 			fst = i;
// 		}
// 		else if(ft_strchr(split[i], '"'))
// 		{
// 			lst = i;
// 		}
// 		if(lst && fst)
// 		{
// 			i = fst + 1;
// 			while (fst < lst)
// 			{
// 				ft_strjoin();
// 				i++;
// 			}
			
// 		}
// 		i++;
// 	}
		
// }


// t_data *parse(char *input, char **envp)
// {
// 	char **split;
// 	t_data	*data;
// 	// t_command	*cmds;
// 	char **strarr;
// 	// int quotes;
// 	int i;
	
	
// 	data = init_data(envp);
// 	split = ft_split(input, ' ');
// 	// quotes = CLOSED;
// 	i = 0;
// 	strarr = NULL;
// 	// mx_print_strarr(split, " ");
// 	while(split[i])
// 	{
// 		if (!ft_strcmp(split[i], "|"))
// 		{
// 			add_command(&data->cmds, create_command(NULL, strarr, data));
// 			free_strarr(strarr);
// 			i++;
// 			strarr = NULL;
// 		}
// 		strarr = add_elem_to_strarr(strarr, split[i]);
// 		fprintf(stderr, "CHECK!\n");
// 		mx_print_strarr(strarr, "\n");
// 		i++;
// 	}
// 	//strarr = add_elem_to_strarr(strarr, split[i]);
// 	add_command(&data->cmds, create_command(NULL, strarr, data));
// 	// free_strarr(split);
// 	// split = connect_quotes();
	
// 	return data;
// }



//here add recognition of where redirection goes
int find_redir(char *input)
{
	int i;

	i = 0;
	while (input[i])
	{
		if(input[i] == '<' || input[i] == '>')
		{
			if(input[i + 1] == '<' || input[i + 1] == '>')
				i++;
			break;
		}
		i++;
	}
	return i;
}

int	get_cmd_ind(int *start, int *end, char *input)
{
	// int redir = -1;
	int i;

	i = *end + 1;
	*start = i;//in future change for detecting redir	
	while(input[i])
	{
		if (input[i] == '|')
		{
			*end = i;
			break;
		}
		i++;
	}
	if(input[i])
		return 1;
	else
	{
		*end = i;	
		return 0;
	}
}

t_data *parse(char *input, char **envp)
{
	t_data	*data;
	char *str;
	int start;
	int end;
	int status;

	start = 0;
	end = -1;
		
	data = init_data(envp);
	while(true)
	{
		status = get_cmd_ind(&start, &end, input);
		fprintf(stderr, "IIII");
		printf("start is %d end is %d status %d\n", start, end, status);
		str = (char *)ft_calloc(sizeof(char) ,(end - start + 1));
		ft_strncpy(str,(input + start), (end - start));
		add_command(&data->cmds, create_command(NULL, ft_split(str, ' '), data)); 
		free(str);
		if(!status)
			break;
	}

	return data;
}


