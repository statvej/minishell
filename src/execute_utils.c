/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchuk <gpinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:20:05 by gpinchuk          #+#    #+#             */
/*   Updated: 2022/11/25 18:22:52 by gpinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**find_path(void)
{
	int		i;
	char	**path;

	i = 0;
	while (ft_strncmp("PATH", g_env[i], 4))
		i++;
	path = ft_split(g_env[i] + 5, ':');
	return (path);
}

char	*command_exec(char *command)
{
	char	*pwd;
	char	*result;

	if (!access(command, F_OK))
		return (command);
	pwd = extend("PWD", 3, 0);
	result = ft_strjoin(pwd, command);
	if (!access(result, F_OK))
	{
		free(pwd);
		return (result);
	}
	free(pwd);
	free(result);
	return (NULL);
}

char	*find_command(char **path, char *command)
{
	int		i;
	char	*result;
	char	*temp;

	i = 0;
	result = command_exec(command);
	if (result)
		return (result);
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		result = ft_strjoin(temp, command);
		if (!access(result, F_OK))
		{
			free(temp);
			return (result);
		}
		free(temp);
		free(result);
		i++;
	}
	return (0);
}
