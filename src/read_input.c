/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:01:13 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/06 15:15:35 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*read_input(void)
{
	char cwd[256];
	getcwd(cwd, sizeof(cwd));
	ft_strcat(cwd, "  ");
	// if (cwd != "\0" || cwd != NULL)
	// 	add_history(cwd);

    return readline(cwd);
}
