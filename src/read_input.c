/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:01:13 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/24 19:11:32 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*read_input(void)
{
	char	*ret;
	char	cwd[256];

	getcwd(cwd, sizeof(cwd));
	ft_strcat(cwd, " : ");
	ret = readline(cwd);
	add_history(ret);
    return (ret);
}
