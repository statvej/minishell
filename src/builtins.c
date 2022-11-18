

#include "../inc/minishell.h"

int env(char *useless)
{
	size_t	i;
	(void)useless;

	i = 0;
	if(!g_env)
		return 0;
	while (g_env[i])
	{
		if (ft_strchr(g_env[i], '='))
		{
			ft_putstr_fd(g_env[i], 1);
			ft_putchar_fd('\n', 1);
		}
		i++;
	}
	return 1;
}

int pwd(char *useless)
{
	(void)useless;
	char cwd[256];
	int ret;
	ret = getcwd(cwd, sizeof(cwd));
	ft_putstr_fd(cwd, 1);
	return ret;
}

int export(char *string)
{
	g_env = realloc_env(string, (size_of_env() + 1));
	if(g_env)
		return 1;
	else
		return 0;
}

int unset(char *string)
{
	g_env = realloc_env(string, (size_of_env() - 1));
	if(g_env)
		return 1;
	else
		return 0;
}