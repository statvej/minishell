/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:24:25 by gpinchuk          #+#    #+#             */
/*   Updated: 2022/10/05 15:55:41 by fstaryk          ###   ########.fr       */
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

typedef struct s_command
{
	char **args;
	char *path;
	struct s_command *next;
	struct s_data *data;
}t_command;

typedef struct s_data
{
	struct s_command   *cmds;
	char **envp;
	int in;
	int out;
	int eout;
}t_data;

//Reading Input

char	*read_input(void);

//Parse

t_data	*parse(char *input, char **envp);

//INitialization

t_data	*init_data(char **envp);

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

#endif
