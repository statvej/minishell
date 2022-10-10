/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:24:25 by gpinchuk          #+#    #+#             */
/*   Updated: 2022/10/10 17:24:38 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdbool.h>
# include "../libft/libft.h"

# define STR_IN 0
# define STR_OUT 1
# define STR_ERR 2
# define OPENED 0
# define CLOSED 1 

# define TEXT 0
# define SPACE 1
# define PIPE 2
# define INPUT 3
# define OUTPUT_OVER 4
# define HERE_DOC 5
# define OUTPUT_APPEND 6
# define DUP_QUOTES 7
# define SING_QUOTES 8
# define SEPARATOR 9

typedef struct s_token_list
{
	int len;
	char *tok;
	int type;
	struct s_token_list *next;
	struct s_token_list *prev;
}t_token_list;
// typedef struct s_inputs
// {
// 	char *input;
// 	struct s_inputs *next;
// }t_inputs;


typedef struct s_command
{
	char **args;
	char *path;
	//struct s_inputs *inp;
	struct s_command *next;
	
	struct s_data *data;
}t_command;

typedef struct s_data
{
	struct s_command   *cmds;
	char **envp;
	char *file_in;
	char *file_out;
	bool here_doc;
	int in;
	int out;
	int eout;
}t_data;

//Destroy

void	free_data(t_data *data);

//Reading Input

char	*read_input(void);

//LEXER

t_token_list *lexer(char *input);

//Parse

t_data	*parse(char *input, char **envp);

//INitialization

t_data	*init_data(char **envp);

//T0KEN STRUCT

t_token_list	*create_token(int length, char *start, int type);
void			add_token(t_token_list **first, t_token_list * to_add);

void			print_token(t_token_list *token);

//Destroy

void    free_strarr(char **strarr);

//Utils 

int		get_str_arr_len(char **strarr);
char	*ft_strjoin_del1(char const *s1, char const *s2);
char ** add_elem_to_strarr(char **strarr, char *str);

//Command struct

t_command	*create_command(char *path, char **args, t_data *data);
void		add_command(t_command **first, t_command *to_add);

//PRINT CHECK

void mx_print_strarr(char **arr, const char *delim);
void print_data(t_data *data);

#endif
