/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchuk <gpinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:02:12 by gpinchuk          #+#    #+#             */
/*   Updated: 2022/11/25 15:05:04 by gpinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	size_of_env(void)
{
	int	i;

	i = 0;
	while (g_env[i])
		i++;
	return (i);
}

int	find_index_of_char(char *env, char c)
{
	char	*ch;

	ch = ft_strchr(env, c);
	if (!ch)
		return (-1);
	return ((size_t)(ch - env));
}

char	*get_env(char *env)
{
	int	i;
	int	j;

	if (!env)
		return (NULL);
	j = ft_strlen(env);
	i = find_keyword(env);
	if (i != -1)
		return (ft_substr(g_env[i], (j + 1), ft_strlen(g_env[i])));
	else
		return (NULL);
}
