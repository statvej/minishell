
#include "../inc/minishell.h"

void put_env(char *temp)
{
	char *str;
	str = ft_strjoin("\"", temp);
	free(temp);
	temp = ft_strjoin(str, "\"");
	ft_putstr_fd(temp, 2);
	free(temp);
	free(str);
}

void print_export()
{
	int i;
	int indx;
	char *sub;
	char *temp;

	i = 0;
	while(g_env[i])
	{
		ft_putstr_fd("declare -x ", 2);
		if((indx = find_index_of_char(g_env[i], '=')) == -1)
			indx = ft_strlen(g_env[i]);
		sub = ft_substr(g_env[i], 0, indx);
		ft_putstr_fd(sub, 2);
		if((ft_strchr(g_env[i], '=')) != NULL)
		{
			temp = get_env(sub);
			ft_putstr_fd("=", 2);
			put_env(temp);
		}
		ft_putstr_fd("\n", 2);
		free(sub);
		i++;
	}
}