/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:24:25 by gpinchuk          #+#    #+#             */
/*   Updated: 2022/10/18 17:03:11 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdbool.h>
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

//DEFINITION OF STANDART FDs

# define STR_IN 0
# define STR_OUT 1
# define STR_ERR 2


# define OPENED 0
# define CLOSED 1 

//TOKEN TYPES

# define TEXT 0
# define SPACE 1
# define PIPE 2
# define INPUT 3
# define OUTPUT_OVER 4
# define HERE_DOC 5
# define OUTPUT_APPEND 6
# define DUP_QUOTES 7
# define SING_QUOTES 8
# define PRNTH_LEFT 10
# define PRNTH_RIGHT 11
# define LOGICAL_AND 12
# define LOGICAL_OR 13
# define SEPAR_MORE 14
# define SEPAR_LESS 15
# define SEPAR_PIPE 16
# define EXTENDED 17

typedef struct s_token_list
{
	int len;
	char *tok;
	int type;
	struct s_token_list *next;
	struct s_token_list *prev;
}t_token_list;

typedef struct s_cmd_group
{
	char **pos_paths;
	char **args;
	int* in;
	int in_size;
	int* out;
	int out_size;
}t_cmd_group;

typedef struct s_pipe_group
{
	t_cmd_group *cmd_group;
	t_token_list *tok_list;
	int tok_len;
	struct s_pipe_group *next;
}t_pipe_group;

typedef struct s_log_group
{
	t_pipe_group *pipe_group;
	t_token_list *tok_list;
	int tok_len;
	int needs;
	int ret;
	struct s_log_group *prev;
	struct s_log_group *next;
}t_log_group;

typedef struct s_data	
{
	t_log_group *log_grp;
	char **envp;
}t_data;

//Destroy

// void	free_data(t_data *data);

//Reading Input

char	*read_input(void);

//LEXER

t_token_list *lexer(char *input);

//Parse

t_data	*parse(t_token_list ** global, char **env);
// t_data	*parse(char *input, char **envp);

//Quotes
void open_extantion_quotes(t_log_group *log_grp, t_data *data);

// //INitialization

// t_data	*init_data(char **envp);

//T0KEN STRUCT

t_token_list	*create_token(int length, char *start, int type);
void			add_token(t_token_list **first, t_token_list * to_add);
t_token_list *token_delim_logic(t_token_list **global, int *len, int *needs);
t_token_list *token_delim_pipe(t_token_list *global, int log_len, int *pipe_len);

//LOG GROUP STRUCT

t_log_group *create_log_group(t_token_list **global);
t_log_group *create_log_link(t_token_list *tok_list, int tok_len, int needs);
void add_log_link(t_log_group **first, t_log_group *to_add);


//PIPE STRUCT

void create_pipe_group(t_log_group *log_grp);

//Destroy

void    free_strarr(char **strarr);

//Utils 

int		get_str_arr_len(char **strarr);
char	*ft_strjoin_del1(char const *s1, char const *s2);
char ** add_elem_to_strarr(char **strarr, char *str);
void restore_tok_list(t_token_list **global);
char	*ft_strnnjoin(char const *s1, int n1, char const *s2, int n2);
void strtoknjoin(t_token_list **start, int lenth);

//Command struct

// t_command	*create_command(char *path, char **args, t_data *data);
// void		add_command(t_command **first, t_command *to_add);

//PRINT CHECK

void mx_print_strarr(char **arr, const char *delim);
void print_logic_grp(t_log_group *log_grp);
void print_ntoken(t_token_list *token, int n, char * depth);
void			print_token(t_token_list *token);

// void print_data(t_data *data);

#endif
