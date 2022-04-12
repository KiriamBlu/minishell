
#include "../../minishell.h"

void	checkforenv(char *cmd, char *arg, t_list *envp)
{
	int i;
	char **args;

	i = -1;
	args = ft_split(arg, ' ');
	if (strcmp("env", cmd) == 0)
	{
		if(args[0])
		{
			freemat(args);
			printf("env: %s: No such file or directory\n", args[0]);
			return ;
		}
		printlist(envp);
	}
	freemat(args);
}

void	cd_update_env(t_minib *minilst)
{
	char	*tmp;
	int		i;
	int		j;

	i = getposinlst(minilst->envp, "OLDPWD");
	j = getposinlst(minilst->envp, "PWD");
	if(i != -1)
	{
		delpos(&minilst->envp, i);
		putinpos(&minilst->envp, i, ft_strjoin("OLDPWD=", getlineinenv(minilst->envp, (j + 1)) + 4));
	}
	else
		putinpos(&minilst->envp, i, ft_strjoin("OLDPWD=", getlineinenv(minilst->envp, 17) + 4));	
	tmp = getcwd(NULL, 0);
	delpos(&minilst->envp, j);
	putinpos(&minilst->envp, j, ft_strjoin("PWD=", tmp));
	j = getposinlst(minilst->exp, "PWD");
	i = getposinlst(minilst->exp, "OLDPWD");
	delpos(&minilst->exp, i);
	putinpos(&minilst->exp, i, ft_strjoin("OLDPWD=", getlineinenv(minilst->exp, j) + 4));
	delpos(&minilst->exp, j);
	putinpos(&minilst->exp, j, ft_strjoin("PWD=", tmp));
	free(tmp);
}

char	*check_pwd(char *str, int home, t_minib *minilst)
{
	char	*s;
	int		i;

	s = NULL;
	if (!str)
	{
		if (home != -1)
			s = ft_strdup(getlineinenv(minilst->envp, home + 1) + 5);
		else
			printf("minishell: cd: HOME not set\n");
	}
	else if(!strcmp(str, "-"))
	{
		i = getposinlst(minilst->envp, "OLDPWD") + 1;
		if(i != 0)
		{
			s = ft_strdup(getlineinenv(minilst->envp, i) + 7);
			printf("%s\n", s);
		}
		else
			printf("minishell: cd: OLDPWD not set\n");
	}
	else
		s = ft_strdup(str);
	return (s);
}


void	checkforcd(char *cmd, char *arg, t_minib *minilst)
{
	char	*str;
	char	**args;

	if (strcmp("cd", cmd) != 0)
		return	;
	args = ft_split(arg, ' ');
	if (getposinlst(minilst->envp, "PWD") == -1)
	{
		minilst->pwd = getcwd(NULL, 0);
		putinpos(&minilst->envp, 16, ft_strjoin("PWD=", minilst->pwd));
	}
	str = check_pwd(args[0], getposinlst(minilst->envp, "HOME"), minilst);
	if(chdir(str) == -1)
	{
		if(!minilst->pwd)
			minilst->pwd = getcwd(NULL, 0);
		if(str)
			printf("minishell: cd: %s: No such file or directory\n", str);
	}
	else
		cd_update_env(minilst);
	freemat(args);
	free(str);
}

void checkforexit(char *cmd, char *arg, t_minib *minilst)//AUX  MAYBE LEAKS
{
	int		i;
	char	**aux;

	i = 0;
	if (strcmp(cmd, "exit") == 0)
	{
		aux = ft_split(arg, ' ');
		printf("exit\n");
		if (!aux[0])
		{
			freemat(aux);
			freeeverything(minilst);
			exit(0);
		}
		if(aux[1])
		{
			printf("minishell: exit: too many arguments\n");
			freemat(aux);
			return ;
		}
		i = -1;
		while(aux[0][++i])
		{
			if(ft_isdigit(aux[0][i]) != 1)
			{
				printf("minishell: exit: %s: numeric argument required\n", aux[0]);
				break ;
			}
		}
		freeeverything(minilst);
		exit(ft_atoi(aux[0]));
	}
}
