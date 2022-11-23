#include "../inc/minishell.h"

int change_dir(char *arg)
{
	char *sub;
	char *temp;

	sub = getcwd(0, 256);
	if(chdir(arg) == ERROR)
		return (-1);
	temp = getcwd(0, 256);
	sub = ft_strjoin("OLDPWD=", sub);
	temp = ft_strjoin("PWD=", temp);
	change_env(sub, find_keyword("OLDPWD"));
	change_env(temp, find_keyword("PWD"));
	return (1);
}

int b_cd (char *arg)
{
	if(!arg)
	{
		if(change_dir(get_env("HOME")) == ERROR)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		}
	}
	else
		if((change_dir(arg)) == -1)
		{
			ft_putstr_fd("cd: no such file or directory: ",2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd("\n", 2);
			return(1);
		}
	return (0);
}
