/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:53:20 by fstaryk           #+#    #+#             */
/*   Updated: 2022/05/04 13:05:07 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	sub_print(int nb, int fd)
{
	int	comper;
	int	fnumber;

	comper = 1000000000;
	while (nb / comper < 1)
	{
		comper = comper / 10;
	}
	while (comper >= 1)
	{
		fnumber = nb / comper + 48;
		ft_putchar_fd(fnumber, fd);
		nb = nb - (nb / comper * comper);
		comper = comper / 10;
	}
}

void	ft_putnbr_fd(int nb, int fd)
{
	if (nb == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	else if (nb == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	else if (nb > 0)
	{
		sub_print(nb, fd);
		return ;
	}
	else if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb = nb * (-1);
		sub_print(nb, fd);
	}
}
