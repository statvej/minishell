/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:27:02 by fstaryk           #+#    #+#             */
/*   Updated: 2022/05/03 21:26:22 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

static char	*fill_string(int n, int comper, int is_minus, char *str)
{
	int	i;
	int	fnumber;

	i = 0;
	if (is_minus == 1)
	{
		str[0] = '-';
		i = 1;
	}
	while (comper >= 1)
	{
		fnumber = n / comper + 48;
		str[i] = fnumber;
		n = n - (n / comper * comper);
		comper = comper / 10;
		i++;
	}
	return (str);
}

static char	*return_min_int(void)
{
	char	*ret;

	ret = ft_strnew(11);
	ret = ft_strcpy(ret, "-2147483648");
	return (ret);
}

static char	*return_zero(void)
{
	char	*ret;

	ret = ft_strnew(1);
	ret = ft_strcpy(ret, "0");
	return (ret);
}

char	*ft_itoa(int n)
{
	int		comper;
	int		size_count;
	int		is_minus;
	char	*ret;

	if (n == -2147483648)
		return (return_min_int());
	else if (n == 0)
		return (return_zero());
	is_minus = 0;
	comper = 1000000000;
	size_count = 10;
	if (n < 0)
	{
		is_minus = 1;
		n *= -1;
	}
	while (n / comper < 1)
	{
		comper = comper / 10;
		size_count--;
	}
	ret = ft_strnew(size_count + is_minus);
	ret = fill_string(n, comper, is_minus, ret);
	return (ret);
}

// int	main(void)
// {
// 	printf("my = %s", ft_itoa(0));
// }
