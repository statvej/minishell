/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: statvej <statvej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:31:59 by statvej           #+#    #+#             */
/*   Updated: 2022/05/05 13:57:06 by statvej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, unsigned long n)
{
	while (n-- && (*(unsigned char *)s1 || *(unsigned char *)s2))
	{
		if (*(unsigned char *)s1 != *(unsigned char *)s2)
		{
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		}
		s1++;
		s2++;
	}
	return (0);
}

// int main(){
//     printf("my : %d    comp :  %d", ft_strncmp("test\200", "test\0", 6),
		//strncmp("test\200", "test\0", 6));
// }
