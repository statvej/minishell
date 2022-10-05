/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:53:45 by fstaryk           #+#    #+#             */
/*   Updated: 2022/10/05 15:56:57 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void mx_print_strarr(char **arr, const char *delim){
	if(!arr || !delim){
		return;
	}
	int exist = 0;
	int i = 0;

	for(; arr[i]; i++){
		ft_putstr_fd(arr[i], 1);
		ft_putstr_fd((char *)delim, 1);
		exist = 1;
	}
}
