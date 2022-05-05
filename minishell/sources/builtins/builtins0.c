
#include "../../minishell.h"

int	checkforenv(char *cmd, t_list *envp, int fileout, int *status)
{
	if (ft_strcmp("env", cmd) == 0)
	{
		printlist(envp, fileout);
		*status = 0;
		return(1);
	}
	return (0);
}

void	updateenv(t_minib *minilst)
{
	char	*tmp;
	int		i;
	int		j;

	i = getposinlst(minilst->envp, "OLDPWD");
	j = getposinlst(minilst->envp, "PWD");
	if(i != -1 && j != -1)
	{
		delpos(&minilst->envp, i);
		putinpos(&minilst->envp, i, ft_strjoin("OLDPWD=", getlineinenv(minilst->envp, (j + 1)) + 4));
	}
	if(j != -1)
	{
		tmp = getcwd(NULL, 0);
		delpos(&minilst->envp, j);
		putinpos(&minilst->envp, j, ft_strjoin("PWD=", tmp));
		free(tmp);
	}
}

void	cd_update_env(t_minib *minilst)
{
	char	*tmp;
	int		i;
	int 	j;

	updateenv(minilst);
	j = getposinlst(minilst->exp, "PWD");
	if(j != -1)
	{
		tmp = getcwd(NULL, 0);
		delpos(&minilst->exp, j);
		putinpos(&minilst->exp, j, ft_strjoin("PWD=", tmp));
		free(tmp);
	}
	i = getposinlst(minilst->exp, "OLDPWD");
	if(i != -1 && j != -1)
	{
		delpos(&minilst->exp, i);
		putinpos(&minilst->exp, i, ft_strjoin("OLDPWD=", getlineinenv(minilst->exp, j) + 4));
	}
}

char	*check_pwd(char *str, int home, t_minib *minilst, int fileout)
{
	char	*s;
	int		i;

	s = NULL;
	if (!str)
	{
		if (home != -1)
			s = ft_strdup(getlineinenv(minilst->envp, home + 1) + 5);
		else
			errorprintf("minishell: cd: HOME not set\n", &minilst->cmdstatus);
	}
	else if(!strcmp(str, "-"))
	{
		i = getposinlst(minilst->envp, "OLDPWD") + 1;
		if(i != 0)
		{
			s = ft_strdup(getlineinenv(minilst->envp, i) + 7);
			ft_putstr_fd(s, fileout);
		}
		else
		{
			errorprintf("minishell: cd: OLDPWD not set\n", &minilst->cmdstatus);
			printf("%d\n", minilst->cmdstatus);
		}
	}
	else
		s = ft_strdup(str);
	return (s);
}


int	checkforcd(char *cmd, char *arg, t_minib *minilst, int fileout)
{
	char	*str;
	char	**args;

	if (ft_strcmp("cd", cmd) != 0)
		return	(0);
	args = ft_split(arg, ' ');
	str = check_pwd(args[0], getposinlst(minilst->envp, "HOME"), minilst, fileout);
	if(chdir(str) == -1)
	{
		if(!minilst->pwd)
			minilst->pwd = getcwd(NULL, 0);
		if(str)
		{
			minilst->cmdstatus = 1;
			printf("minishell: cd: %s: No such file or directory\n", str);
		}
	}
	else
	{
		cd_update_env(minilst);
		minilst->cmdstatus = 0;
	}
	freemat(args);
	free(str);
	return(1);
}

int checkforexit(char *cmd, char *arg, t_minib *minilst)//AUX  MAYBE LEAKS
{
	int		i;
	char	**aux;

	i = 0;
	if (ft_strcmp(cmd, "exit") == 0)
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
			errorprintf("minishell: exit: too many arguments\n", &minilst->cmdstatus);
			freemat(aux);
			return (1);
		}
		i = -1;
		while(aux[0][++i])
		{
			if(ft_isdigit(aux[0][i]) != 1)
			{
				printf("minishell: exit: %s: numeric argument required\n", aux[0]);
				minilst->cmdstatus = 255;
				break ;
			}
		}
		freeeverything(minilst);
		exit(ft_atoi(aux[0]));
	}
	return(0);
}
