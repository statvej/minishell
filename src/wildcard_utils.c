/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:43:33 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/25 14:47:25 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*add_wildcard_ref(t_str_list **ret, char *ref, int *temp_len, int first)
{
	add_to_str_list(ret, \
				create_str_link(ft_strndup(ref, *temp_len), *temp_len, first));
	*temp_len = 0;
	return (NULL);
}

void	init_get_req_parts(int *i, int *temp_len, int *f)
{
	*f = S_START;
	*i = 0;
	*temp_len = 0;
}

char	*sub_get_req_parts(char *str, int *temp_len)
{
	*temp_len += 1;
	return (str);
}

t_str_list	*get_req_parts(char *str, int len)
{
	int			i;
	int			tl;
	char		*rf;
	t_str_list	*ret;
	int			first;

	rf = NULL;
	ret = NULL;
	init_get_req_parts(&i, &tl, &first);
	if (check_if_str_filled_with_c(str, len, '*'))
		return (create_str_link(NULL, 0, STAR_ULTIMATE));
	while (str[i] && i < len)
	{
		if (!rf && str[i] != '*')
			rf = sub_get_req_parts(&str[i], &tl);
		else if (rf && str[i] == '*')
			rf = add_wildcard_ref(&ret, rf, &tl, first);
		else if (rf && str[i] != '*')
			tl++;
		if (str[i++] == '*')
			first = 0;
	}
	if (rf)
		add_to_str_list(&ret, create_str_link(ft_strndup(rf, tl), tl, S_END));
	return (ret);
}
