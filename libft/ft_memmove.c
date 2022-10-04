/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: statvej <statvej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 11:34:18 by fstaryk           #+#    #+#             */
/*   Updated: 2022/05/05 13:56:08 by statvej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, unsigned int len)
{
	void			*ret;
	unsigned char	*temp_dst;
	unsigned char	*temp_src;

	ret = dst;
	temp_dst = (unsigned char *)dst;
	temp_src = (unsigned char *)src;
	if (dst == src || len == 0 || !dst || !src)
	{
		return (dst);
	}
	if (dst > src)
	{
		while (len > 0)
		{
			temp_dst[len - 1] = temp_src[len - 1];
			len--;
		}
	}
	else
	{
		ft_memcpy(dst, src, len);
	}
	return (ret);
}
// int main() {
// 	char	*ft_dst;
// 	char	src[] = "ABCDEFG";
// 	size_t	size = 5;
// 	ft_dst = &src[2];

//     ft_memmove(ft_dst, src, size);
//     fprintf(stderr, "%s", ft_dst);
//     return (9);
// }