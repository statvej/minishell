/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:01:13 by fstaryk           #+#    #+#             */
/*   Updated: 2022/10/06 13:24:32 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*read_input(void)
{
	char cwd[256];
	// char *end;
	// end = (fchar *)malloc(sizeof(char) * 256);
	// end = ft_strrchr(cwd, '/');
	getcwd(cwd, sizeof(cwd));
	ft_strcat(cwd, "  ");
    return readline(cwd);
}
