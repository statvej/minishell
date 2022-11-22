/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:14:34 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/22 18:25:33 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int check_compatability(t_str_list *str_list, char *dir_member)
{
    int i;
    t_str_list* temp_link;

    i = 0;
    temp_link = str_list;
    while (dir_member[i] && temp_link)
    {
        if(str_list->strict && str_list == temp_link && i)
            return 0;
        if(ft_strncmp(&dir_member[i], temp_link->str, temp_link->len) == 0)
        {
            if (!temp_link->next && temp_link->strict && i + temp_link->len != (int)ft_strlen(dir_member))
                return 0;
            temp_link = temp_link->next;
        }
        i++;
    }
    if(temp_link == str_list)
        return 0;
    else
        return 1;
}

t_str_list *get_req_parts(char *str, int len)
{
    int i;
    int temp_len;
    char *ref;
    t_str_list *ret;
    int first;

    ref = NULL;
    i = 0;
    temp_len = 0;
    ret = NULL;
    first = STRICT_START;
    while (str[i] && i < len)
    {
        if(!ref && str[i] != '*')
        {
            ref = &str[i];
            temp_len++;
        }
        else if(ref && str[i] == '*')
        {
            add_to_str_list(&ret, create_str_link(ft_strndup(ref, temp_len), temp_len, first));
            temp_len = 0;
            ref = NULL;
        }
        else if(ref && str[i] != '*')
            temp_len++;
        if(str[i] == '*')
            first = 0;
        i++;
    }
    if(ref)
    {
        if(ret)
            add_to_str_list(&ret, create_str_link(ft_strndup(ref, temp_len), temp_len, STRICT_END));
        else
            add_to_str_list(&ret, create_str_link(ft_strndup(ref, temp_len), temp_len, 0));
    }
    return ret;    
}

int proccess_wildcard(t_token_list *link)
{
    t_str_list *str_list;
    DIR *dir;
    t_dirent *dir_entry;
    
    str_list = get_req_parts(link->tok, link->len);
    link->type = WILDCARD_REMOVE;
    dir = opendir(".");
    print_check_str_list(str_list);   
    dir_entry = readdir(dir);
    while (dir_entry)
    {
        if(check_compatability(str_list, dir_entry->d_name))
        {
            printf("%s is compatable\n", dir_entry->d_name);
            //add new token
        }
        else
            printf("%s doesnt fit\n", dir_entry->d_name);
        dir_entry = readdir(dir);
    }
    free_str_list(&str_list); 
    return 1;
}

// Works only for current directory
int extend_wildcards(t_token_list *tok_list)
{
	int i;
	int ret;

    ret = 1;
	while(tok_list)
	{
		i = 0;
		while (tok_list->tok[i] && i < tok_list->len)
		{
			if(tok_list->tok[i] == '*')
            {
				ret = proccess_wildcard(tok_list);
                break;
            }
            i++;
		}
		tok_list = tok_list->next;
	}
    return ret;
}
