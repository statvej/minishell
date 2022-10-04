/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 11:34:15 by fstaryk           #+#    #+#             */
/*   Updated: 2022/05/01 18:21:54 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void			*ret;
	unsigned int	count;

	ret = dst;
	count = 0;
	while (count < n)
	{
		((unsigned char *)dst)[count] = ((unsigned char *)src)[count];
		count++;
	}
	return (ret);
}
// int main(){
//     char str1[100] = "11112436583456278346523746529387465";
//     char str2[100] = "wjhbgwhrthgkwehbgwrgehlj2ghrf";
//     ft_memcpy(str1, str2, 10);
//     printf("%s", str1);
// }
