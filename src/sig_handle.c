/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:56:35 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/26 16:00:58 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	prompt(void)
{
	char	cwd[256];

	getcwd(cwd, sizeof(cwd));
	ft_strcat(cwd, " : ");
	ft_putstr_fd(cwd, 1);
}

void	sig_handle(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		prompt();
	}
}

void	sig_handle_child(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
	}	
	if (sig == SIGINT)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

void	heredoc_sig_handle(int sig)
{
	if (sig == SIGINT)
	{
		exit(EXIT_FAILURE);
	}
}
