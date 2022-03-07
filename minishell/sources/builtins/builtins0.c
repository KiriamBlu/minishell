
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

void	cd_update_env(int i[2], t_minib *minilst)
{
	char	*tmp;
	int		j[2];

	delpos(&minilst->envp, i[1]);
	putinpos(&minilst->envp, i[1], ft_strjoin("OLDPWD=", getlineinenv(minilst->envp, i[0]) + 4));
	tmp = getcwd(NULL, 0);
	delpos(&minilst->envp, i[0]);
	putinpos(&minilst->envp, i[0], ft_strjoin("PWD=", tmp));
	j[0] = getposinlst(minilst->exp, "PWD");
	j[1] = getposinlst(minilst->exp, "OLDPWD");
	delpos(&minilst->exp, j[1]);
	putinpos(&minilst->exp, j[1], ft_strjoin("OLDPWD=", getlineinenv(minilst->exp, j[0]) + 4));
	delpos(&minilst->exp, j[0]);
	putinpos(&minilst->exp, j[0], ft_strjoin("PWD=", tmp));
	free(tmp);
}

char	*check_pwd(char *str, int home, int opwd, t_minib *minilst)
{
	char	*s;

	s = NULL;
	if (!str)
	{
		if (home != -1)
			s = ft_strdup(getlineinenv(minilst->envp, home) + 5);
		else
			printf("minishell: cd: HOME not set\n");
	}
	else if(!ft_strncmp(str, "-", ft_strlen(str)))
	{
		if(opwd != -1)
		{
			s = ft_strdup(getlineinenv(minilst->envp, opwd) + 7);
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
	int		i[2];
	char	**args;

	if (strcmp("cd", cmd) != 0)
		return	;
	args = ft_split(arg, ' ');
	if (getposinlst(minilst->envp, "PWD") != -1)
	{
		minilst->pwd = getcwd(NULL, 0);
		putinpos(&minilst->envp, 16, minilst->pwd);
	}
	i[0] = getposinlst(minilst->envp, "PWD");
	i[1] = getposinlst(minilst->envp, "OLDPWD");
	str = check_pwd(args[0], getposinlst(minilst->envp, "HOME") + 1, getposinlst(minilst->envp, "OLDPWD"), minilst);
	if(chdir(str) == -1)
	{
		if(!minilst->pwd)
			minilst->pwd = getcwd(NULL, 0);
		if(str)
			printf("minishell: cd: %s: No such file or directory\n", str);
	}
	else
		cd_update_env(i, minilst);
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
		if(aux[1]) //SALIDA EN CASO DE MAS DE DOS ARGS
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
