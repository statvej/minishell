/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:36:00 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/26 19:58:59 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

//DEFINITION OF STANDART FDs

# define STD_IN 0
# define STD_OUT 1
# define STD_ERR 2

# define ERROR -1
# define SUCCESS 1

# define OPENED 0
# define CLOSED 1

//Defines for Parenthesis

# define S_START 1
# define S_END 2
# define STAR_ULTIMATE 3

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
# define REDIRECTIONS 18
# define WILDCARD_REMOVE 19

typedef struct dirent	t_dirent;

typedef struct s_int_list
{
	int					val;
	struct s_int_list	*next;
}						t_int_list;

typedef struct s_str_list
{
	char				*str;
	int					len;
	int					strict;
	struct s_str_list	*next;
}						t_str_list;

typedef struct s_token_list
{
	int					len;
	char				*tok;
	int					type;
	struct s_token_list	*next;
	struct s_token_list	*prev;
}						t_token_list;

typedef struct s_cmd_group
{
	char				**args;
	char				*limit;
	int					here_pipes[2];
	int					pipes[2];
	pid_t				child;
	char				*command;
	struct s_int_list	*in;
	struct s_int_list	*out;
}						t_cmd_group;

typedef struct s_pipe_group
{
	t_cmd_group			*cmd_group;
	t_token_list		*tok_list;
	int					tok_len;
	struct s_pipe_group	*next;
	struct s_pipe_group	*prev;
}						t_pipe_group;

typedef struct s_log_group
{
	t_pipe_group		*pipe_group;
	t_token_list		*tok_list;
	int					tok_len;
	int					rec_depth;
	int					needs;
	int					ret;
	struct s_log_group	*prev;
	struct s_log_group	*next;
}						t_log_group;

typedef struct s_data
{
	char				*input;
	t_log_group			*log_grp;
	int					last_log_ret;
	char				**pos_paths;
}						t_data;

char					**g_env;

//Destroy

void					free_data_in_loop(t_data *data);

//Reading Input

char					*read_input(void);

//LEXER

t_token_list			*lexer(char *input);
void					init_separs(char **separs);
void					init_index(int *index);
int						get_type(char input);
int						add_quot_tok(t_token_list **token, char *input,
							char **start, int *type);
void					add_common_tok(t_token_list **token, char *in,
							char **start, int *type);

//Parse

t_data					*parse(t_token_list **global, int last_ret);

//Quotes
int						parse_actions(t_log_group *log_grp, t_data *data);

//T0KEN STRUCT

t_token_list			*create_token(int length, char *start, int type);
void					add_token(t_token_list **first, t_token_list *to_add);
void					insert_token_after(t_token_list *insert_ref,
							t_token_list *to_add);
t_token_list			*token_delim_logic(t_token_list *global, int *len,
							int *needs);
t_token_list			*token_delim_pipe(t_token_list *global, int log_len,
							int *pipe_len);
t_token_list			*skip_n_token(t_token_list *global, int count);

//LOG GROUP STRUCT

t_log_group				*create_log_group(t_token_list *global);
t_log_group				*create_log_link(t_token_list *tok_list, int tok_len,
							int needs);
void					add_log_link(t_log_group **first, t_log_group *to_add);

//PIPE STRUCT

void					create_pipe_group(t_log_group *log_grp);

//Destroy

void					free_strarr(char **strarr);
t_token_list			*free_tokens(t_token_list *tok);

//Utils

int						get_str_arr_len(char **strarr);
char					*ft_strjoin_del1(char const *s1, char const *s2);
char					**add_elem_to_strarr(char **strarr, char *str);
void					restore_tok_list(t_token_list **global);
char					*ft_strnnjoin(char const *s1, int n1, char const *s2,
							int n2);
void					strtoknjoin(t_token_list **start, int lenth);
int						check_if_str_filled_with_c(char *str, int len, char c);

//PRINT CHECK

void					mx_print_strarr(char **arr, const char *delim);
void					print_logic_grp(t_log_group *log_grp);
void					print_ntoken(t_token_list *token, int n, char *depth);
void					print_token(t_token_list *token);
void					print_cmd(t_cmd_group *cmd_grp);
void					printBits(size_t const size, void const *const ptr);
void					print_check_str_list(t_str_list *list);
void					restore_tok_list(t_token_list **global);

//INT LISTS

t_int_list				*create_int_link(int val);
void					add_to_int_list(t_int_list **list, t_int_list *to_add);

//CMD
int						open_redir(t_pipe_group *pipe);
t_cmd_group				*create_cmdgrp(void);
int						create_args(t_pipe_group *pipe);
int						redirect(int type, char *file, int len,
							t_cmd_group **cmds);

//extention quotes

char					*extend(char *var, int len, int last_ret);
void					open_extentions(t_token_list **tok_list, int tok_len,
							int last_ret);
void					open_quotes(t_token_list **tok_list, int *tok_lenth);

//lexical errors

int						check_lexical_errors(t_token_list *list);
int						check_prnth_location(t_token_list *l);

//execution

int						execution(t_data *data);
char					**find_path(void);
void					process(t_cmd_group *cmd_grp, char **pp);
int						create_pipes(t_log_group *log_grp);
void					close_pipes(t_pipe_group *pipe_grp);
char					*find_command(char **path, char *command);
t_log_group				*execute_log(t_data *data, t_log_group *log_grp, \
															int cur_level);
void					redirect_pipes(t_cmd_group *temp_cmd, \
												t_pipe_group *pipe_grp);

//Signals

void					sig_handle(int sig);

//RECURSION DEPTH

int						set_recursion_depth(t_log_group *log_grp);

//Environment

char					**set_env(void);

//HERE DOC

void					fill_here_doc(int fd, char *limit);
int						exists(const char *fname);

//ENV
char					**create_env(char **env);
int						size_of_env(void);
void					print_env(void);
char					*get_env(char *env);
void					set_new(char *arg);
void					change_env(char *arg, int index);
int						find_index_of_char(char *env, char c);
char					**realloc_env(size_t size);
int						compare_key(char *env, char *string);
int						find_keyword(char *keyword);

//CHECKERS

int						is_group(t_token_list *list);
int						is_log_group(t_token_list *list);
int						is_prnth(t_token_list *list);
int						is_redir(t_token_list *list);

//BUILTINS
int						check_builtin(t_cmd_group *temp_cmd);
int						exec_buin(t_cmd_group *temp_cmd, t_data *data);
int						b_pwd(void);
int						b_env(void);
int						b_cd(char *arg);
int						b_echo(char **args);
int						b_export(char **args);
void					print_export(void);
int						b_unset(char **args);
int						b_exit(char **av, t_data *data);

//String list func

t_str_list				*create_str_link(char *str, int len, int strict);
void					add_to_str_list(t_str_list **list, t_str_list *to_add);
void					free_str_list(t_str_list **list);

//Wildcards

int						extend_wildcards(t_token_list *tok_list);
t_str_list				*get_req_parts(char *str, int len);

//Signals
void					signals(void);
void					child_sig(void);
void					heredoc_sig(void);
void					heredoc_sig_handle(int sig);
void					sig_handle(int sig);
void					sig_handle_child(int sig);

#endif
