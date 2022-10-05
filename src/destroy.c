/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:36:45 by fstaryk           #+#    #+#             */
/*   Updated: 2022/10/05 15:45:29 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void    free_strarr(char **strarr)
{
    int i;

    i = 0;
    if(!strarr)
        return;
    while(strarr[i] != NULL)
    {
        free(strarr[i]);
    }
    free(strarr);
}
