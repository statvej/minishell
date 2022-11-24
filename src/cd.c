/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 18:53:56 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/24 19:45:56 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	change_dir(char *arg)
{
	char	*sub;
	char	*temp;
	int		i;
	char	*str1;
	char	*str2;

	sub = getcwd(0, 256);
	if (chdir(arg) == ERROR)
		return (-1);
	temp = getcwd(0, 256);
	str1 = ft_strjoin("OLDPWD=", sub);
	str2 = ft_strjoin("PWD=", temp);
	i = find_keyword("OLDPWD");
	if (i != -1)
		change_env(str1, i);
	else
		set_new(str1);
	i = find_keyword("PWD");
	if (i != -1)
		change_env(str2, i);
	else
		set_new(str2);
	free(sub);
	free(temp);
	return (1);
}

int	b_cd(char *arg)
{
	if (!arg)
	{
		if (change_dir(get_env("HOME")) == ERROR)
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	}
	else
	{
		if (change_dir(arg) == -1)
		{
			ft_putstr_fd("cd: no such file or directory: ", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd("\n", 2);
			return (1);
		}
	}
	return (0);
}
