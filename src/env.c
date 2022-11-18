

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

char **realloc_env(char *string, size_t new_size)
{
	char** new_env;
	int i;
	int j;

	if(new_size < size_of_env())
		j = 0;
	else
		j = 1;
	new_env = (char **)malloc(sizeof(char *) * (new_size + 1));
	i = 0;
	while (g_env[i])
	{
		new_env[i] = ft_strdup(g_env[i]);
		i++;
	}
	new_env[i] = NULL;
	free_strarr(g_env);
	//print_env(new_env);
	return new_env;
}
