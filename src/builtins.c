/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 19:06:54 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/22 19:57:58 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../inc/minishell.h"

int check_builtin(t_cmd_group *temp_cmd)
{
	ft_string_lower(temp_cmd->args[0]);
	if(ft_strcmp(temp_cmd->args[0], "pwd") == 0)
		return (1);
	else if(ft_strcmp(temp_cmd->args[0], "env") == 0)
		return (2);
	else if(ft_strcmp(temp_cmd->args[0], "unset") == 0)
		return (3);
	else if(ft_strcmp(temp_cmd->args[0], "echo") == 0)
		return (4);
	else if(ft_strcmp(temp_cmd->args[0], "export") == 0)
		return (5);
	return -1;
}

int exec_buin(t_cmd_group *temp_cmd)
{
	if(ft_strcmp(temp_cmd->args[0], "pwd") == 0)
		return (b_pwd());
	else if(ft_strcmp(temp_cmd->args[0], "env") == 0)
		return (b_env());
	else if(ft_strcmp(temp_cmd->args[0], "unset") == 0)
		return (b_unset(&temp_cmd->args[1]));	
	else if(ft_strcmp(temp_cmd->args[0], "echo") == 0)
		return (b_echo(temp_cmd->args));
	else if(ft_strcmp(temp_cmd->args[0], "export") == 0)
		return (b_export(&temp_cmd->args[1]));
	
	return -1;
}

int b_env(void)
{
	if(!g_env)
		return 1;
	print_env();
	return 0;
}

int b_pwd(void)
{
	char cwd[256];
	int ret;

	if(getcwd(cwd, sizeof(cwd)))
		ret = 1;
	else
		ret = 0;
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	return ret;
}
