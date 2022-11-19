/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 19:06:54 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/19 19:27:11 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../inc/minishell.h"

int check_builtin(t_cmd_group *temp_cmd)
{
	int i;

	i = -1;
	ft_string_lower(temp_cmd->args[0]);
	if((i = ft_strcmp(temp_cmd->args[0], "pwd")) == 0)
		pwd();
	else if((i = ft_strcmp(temp_cmd->args[0], "env")) == 0)
		env();
	else if((i = ft_strcmp(temp_cmd->args[0], "unset")) == 0)
		unset(&temp_cmd->args[1]);
	if(i == 0)
		exit(1);
	return 1;
}

int env(void)
{
	size_t	i;

	i = 0;
	if(!g_env)
		return 0;
	while (g_env[i])
	{
		if (ft_strchr(g_env[i], '='))
		{
			ft_putstr_fd(g_env[i], 1);
			ft_putchar_fd('\n', 1);
		}
		i++;
	}
	return 1;
}

int pwd(void)
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

// int export(char **args)
// {
// 	int i;

// 	if(!ft_strchr(string, '='))
// 		return 1;
// 	i = 0;
// 	while(g_env[i])
// 	{
// 		if(compare_key(g_env[i], string))
// 			break;
// 		i++;
// 	}
// 	if(i < size_of_env())
// 	{
// 		free(g_env[i]);
// 		g_env[i] = ft_strdup(string);
// 	}
// 	else
// 	{
// 		g_env = realloc_env(size_of_env() + 1);
// 		g_env[i + 1] = ft_strdup(string);
// 		g_env[i + 2] = NULL;
// 	}
// 	if(g_env)
// 		return 1;
// 	else
// 		return 0;
// }

char **delete_env(int index)
{
	char	*tmp;
	int	size;

	size = size_of_env();
	while (g_env[index + 1])
	{
		tmp = ft_strdup(g_env[index + 1]);
		free(g_env[index]);
		g_env[index] = tmp;
		index++;
	}
	return (realloc_env((size - 1)));
}

int unset(char **args)
{
	int i;
	int j;

	i = 0;
	while(args[i])
	{
		j = find_keyword(args[i]);
		if (j != -1)
		{
			if (g_env[j])
				g_env = delete_env(j);
		}
		else
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		i++;
	}
	return 1;
}