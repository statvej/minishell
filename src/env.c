

#include "../inc/minishell.h"

void print_env(char **env)
{
	int i = 0;
	while(env[i])
	{
		fprintf(stderr, "%s\n", env[i]);
		i++;
	}
}

char *shell_lvl(char *env_lvl)
{
	char *level;
	char *ret;
	int i;

	env_lvl += 6;
	level = (char *)malloc(sizeof(char) * ft_strlen(env_lvl));
	i = ft_atoi(env_lvl);
	free(level);
	i++;
	level = ft_itoa(i);
	ret = ft_strjoin("SHLVL=", level);
	free(level);
	return ret;
}

char **create_env(char **env)
{
	char **new_env;
	int i;

	i = 0;
	while(env[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		if(ft_strncmp("SHLVL", env[i], 5) == 0)
		{
			new_env[i] = shell_lvl(env[i]);
		}
		else
			new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	//print_env(new_env);
	return new_env;
}

int size_of_env()
{
	int i;

	i = 0;
	while(g_env[i])
		i++;
	return i;
}

int find_index_of_char(char *env, char c)
{
	char	*ch;

	ch = ft_strchr(env, c);
	if (!ch)
		return (-1);
	return ((size_t)(ch - env));
}

int find_keyword(char *keyword)
{
	int i;
	int index;
	char *sub;

	i = 0;
	if (!keyword)
		return(-1);
	while (g_env[i])
	{
		if ((index = find_index_of_char(g_env[i], '=')) == -1)
			index = ft_strlen(g_env[i]);
		if ((sub = ft_substr(g_env[i], 0, index)))
		{	
			if(ft_strcmp(sub, keyword) == 0)
			{
				free(sub);
				return i;
			}
			free(sub);
		}
		i++;
	}
	return -1;
}

char *get_env(char *env)
{
	int i;
	int j;

	j = ft_strlen(env);
	if((i = find_keyword(env)) != -1)
		return(ft_substr(g_env[i], (j + 1), ft_strlen(g_env[i])));
	else
		return NULL;

}

char **realloc_env(size_t size)
{
	char **new_env;
	int i;

	new_env = (char **)malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (g_env[i])
	{
		new_env[i] = ft_strdup(g_env[i]);
		i++;
	}
	new_env[i] = 0;
	free_strarr(g_env);
	return new_env;
}
