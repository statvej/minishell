/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 11:33:41 by fstaryk           #+#    #+#             */
/*   Updated: 2022/05/03 21:26:00 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ret;

	if (nmemb == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	ret = malloc(nmemb * size);
	if (ret == NULL)
		return (NULL);
	ft_bzero(ret, size * nmemb);
	return (ret);
}
// int main(){
// 	if(!calloc(SIZE_MAX, 10))
// 		printf("HAIPUEM PARNI");
// }
