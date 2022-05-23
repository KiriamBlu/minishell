
#include "../minishell.h"

void	checkeverything(char *line, t_minib *minilst);
void	ejecucion(t_minib *minilst, int i, int num, int flag);
int		prepline(char *line, t_minib *minilst);
void	checkenvp(t_minib *minilst);

/*BASIC STRUCTURE OF THE MINISHELL. THIS IS THE CODE WICH MANAGES THE ENTIRE STRUCTURE AND EXECUTION OF THE PROGRAM*/

int	main(int argc, const char **argv, char **envp)
{
	t_minib	minilst;
	char *line;
	char *promt;
	int		i;

	(void)argv;
	if(argc != 1)
		exit(0);
	i = 0;
	prepbasics(&minilst, envp); //PREPARES THE BASIC THINGS NEEDED FOR THE EXECUTION
	minilst.promt = dopromt(&minilst); //NOT RELEVANT NEITHER NECESARY FOR THE EXECUTION
	while(1)
	{
		inputsignal(); //OPENS SIGNALS
		promt = ft_strdup(minilst.promt);
		line = readline(promt); //READS FROM THE TERMINAL THE LINE THAT WILL HAVE THE CMD AND ARGS
		if(!line) //CTRL D MID EXECUTION
		{
			printf("exit\n");
			if (i > 0)
				freecmds(&minilst);
			exit(0);
		}
		if (ft_strlen(line) != 0 && checkforspaces(line) != 0 && line) //ALLOWS THE PROGRAM TO FILTER NOT REAL CMDS LIKE SPACES AND EMPTY LINES
		{
			add_history(line); //GETS CMDS TO REGISTER INTO THE HISTORY
			checkeverything(line, &minilst); //AFTER ALL THE FILTERS THE EXPANDER->LEXER->PARSERS->EXECTION IS MANEGED HERE.
			i++;
		}
		freecmds(&minilst); //FINISHES THE EXECUTION AND FREEZES EVERYTHING
		free(line);
		free(promt);
	}
	free(minilst.promt);
	return 0;
}

/*CHECK_EVERYTHING WILL PARSE AND MANAGE EVERY PART OF A COMPLEX EXECUTION OF A CMD.*/

void	checkeverything(char *line, t_minib *minilst)
{
	int i;
	int files[4];//filein 0 filein2 1 fileout 2 folout2 3

	i = -1;
	if(prepline(line, minilst) == -1) //PARSES THE LINE TO BE ABLE TO  MAKE IT UNDESRSTANDABLE FOR THE PROGRAM
		return ;
	if (checkinout(minilst) == -1) //CHECKS IF EVERY FILE THAT WILL BE USED WITH THE CMDS IS RIGHT
		return ;
	if (minilst->cmds[0].cmd && ft_strlen(minilst->cmds[0].cmd) != 0) //PARSE CHECKS (REALLY NOT NECESARY ONLY FOR REDUNDANCE)
	{
		files[2] = dup(STDOUT_FILENO);
		files[3] = files[2];
		files[0] = dup(STDIN_FILENO);
		files[1] = files[0];
		while(++i < minilst->cmdnum) //EXECUTES ALL CMDS
		{
			if (minilst->cmdnum > 1)
			{
				while (i < minilst->cmdnum)
				{
					dup2(minilst->cmds[i].filein, STDIN_FILENO);
					dup2(minilst->cmds[i].fileout, STDOUT_FILENO);
					if (ft_strcmp(minilst->cmds[i].cmd, "exit") != 0)
						simba(minilst, i);
					i++;
				}
				i = -1;
				while (++i < minilst->cmdnum)
					wait(&(minilst->cmds[i].pid));
			}
			else
			{
				dup2(minilst->cmds[i].filein, STDIN_FILENO);
				dup2(minilst->cmds[i].fileout, STDOUT_FILENO);
				ejecucion(minilst, i, 1, 0);
			}
		}
		dup2(files[0], STDIN_FILENO);
		close(files[0]);
		dup2(files[2], STDOUT_FILENO);
		close(files[2]);
	}
}

void checkenvp(t_minib *minilst)
{
	char *tmp;
	char *aux;
	char *auxi;
	int j;

	if(getposinlst(minilst->envp, "SHLVL") == -1)
	{
		tmp = ft_strjoin("SHLVL=", "1");
		minilst->shlvl = 1;
		ft_lstadd_back(&minilst->envp, ft_lstnew(ft_strdup(tmp)));
		minilst->shlvl = 1;
		free(tmp);
	}
	if(getposinlst(minilst->envp, "PWD") == -1)
	{
		tmp = ft_strjoin("PWD=", minilst->pwd);
		ft_lstadd_back(&minilst->envp, ft_lstnew(ft_strdup(tmp)));
		free(tmp);
	}
	else
	{
		j = getposinlst(minilst->envp, "SHLVL");
		aux = ft_strdup(getlineinenv(minilst->envp, j + 1));
		auxi = getnamevariable(aux);
		tmp = ft_substr(aux, ft_strlen(auxi) + 1, ft_strlen(aux));
		free(aux);
		free(auxi);
		minilst->shlvl = ft_atoi(tmp) + 1;
		free(tmp);
		aux = ft_itoa(minilst->shlvl);
		tmp = ft_strjoin("SHLVL=", aux);
		putinpos(&minilst->envp, j + 1, ft_strdup(tmp));
		delpos(&minilst->envp, j);
		free(aux);
		free(tmp);
	}
	if(getposinlst(minilst->envp, "_") == -1)
	{
		tmp = ft_strjoin("_=", "/usr/bin/env");
		ft_lstadd_back(&minilst->envp, ft_lstnew(ft_strdup(tmp)));
		free(tmp);
	}
}
	
/*PREPARES THE LISTS FOR THE ENVP EN EXPORT OR SETTS THE NECESARY BASIC VARIABLES FOR THE EXECUTION*/

void prepbasics(t_minib *minilst, char **envp)
{
	int i;
	char **aux;
	char **tmp;

	minilst->pwd = getcwd(NULL, 0);
	i = 0;
	minilst->envp = createarraylst(envp);
	checkenvp(minilst);
	tmp = createlstarray(minilst->envp, ft_lstsize(minilst->envp)); //BUILDS ENVP LIST
	while(tmp[i])
		i++;
	aux = getdonexp(tmp, i);
	freemat(tmp);
	minilst->exp = createarraylst(aux); //BUILDS EXPORT LIST 
	if(getposinlst(minilst->envp, "OLDPWD") == -1)
		putinpos(&minilst->exp, getgoodpositionexp(minilst->exp, "OLDPWD"), getaddedexp("OLDPWD"));
	minilst->cmdstatus = 0;
	freemat(aux);
}

/*AS IT NAME SAYS IT PRERPARES THE INCOMING 
LINES TO EXPAND, FILTER, SPLITS, AND MAKES PRETTY THE LINE AND PREPARES THE STRUCTURE =)*/

int	prepline(char *line, t_minib *minilst)
{
	int i;
	int a;
	char	**newline;
	char	*expanded;

	i = 0;
	a = 1;
	expanded = ft_strdup(line);
	while(countdollars(expanded) > 0) //CONFIRMAR LEGALIDAD DE ESTO
		expanded = expander(expanded, minilst, i, a);
	newline = lexer(expanded); //WITH THE EXPANDED LINE RETURNS A MATRIX WITH THE LINE "SPLITTED" BY PIPES
	minilst->cmds = malloc(sizeof(t_cmds) * num_matrix(newline)); //PREP STRUCTURE
	minilst->cmdnum = num_matrix(newline);
	while(i < minilst->cmdnum)
	{
		minilst->cmds[i].filein = STDIN_FILENO;
		minilst->cmds[i].fileout = STDOUT_FILENO;
		minilst->cmds[i].cmd = NULL;
		minilst->cmds[i].args = NULL;
		i++;
	}
	i = morfeo(minilst->cmds, newline); //FILLS THE STRUCTURE WITH THE COMAND, ARGS, FILEIN, FILEOUT.
	freemat(newline);
	free(expanded);
	return(i);
}

/*DOES THE ACTUAL EXECUTION OF CMDS AND FILTERS BETWEEN BUILTINS AND NON BUILTINS*/

void ejecucion(t_minib *minilst, int i, int num, int flag)
{
	int		k;
	char	*aux;

	aux = ft_strjoin("_=", minilst->cmds[i].cmd); //FROM HERE
	k = getposinlst(minilst->envp, "_");
	if(k != -1)							//IT PUTS IN ENV THE LAST CMD
	{
		delpos(&minilst->envp, k);
		putinpos(&minilst->envp, k, aux);
	}
	else
	{
		putinpos(&minilst->envp, 0, aux);
	}//UNTILL HERE
	k = 0; //THIS [K] ALLOWS THE PROGRAM TO KNOW IF THE CMD IS BUITLIN OR NOT
	k += checkforexit(minilst->cmds[i].cmd, minilst->cmds[i].args, minilst);
	k += checkforcd(minilst->cmds[i].cmd, minilst->cmds[i].args, minilst, minilst->cmds[i].fileout);
	k += checkforenv(minilst->cmds[i].cmd, minilst->envp, minilst->cmds[i].fileout, &minilst->cmdstatus);
	k += checkforecho(minilst->cmds[i].cmd, minilst->cmds[i].args, minilst->cmds[i].fileout, &minilst->cmdstatus);
	if (ft_strcmp(minilst->cmds[i].cmd, "pwd") == 0 || ft_strcmp(minilst->cmds[i].cmd, "/bin/pwd") == 0)
	{
		free(minilst->pwd);
		minilst->pwd = getcwd(NULL, 0);
		ft_putstr_fd(minilst->pwd, minilst->cmds[i].fileout);
		ft_putchar_fd('\n', minilst->cmds[i].fileout);
		k += 1;
	}
	k += checkforexport(minilst->cmds[i].cmd, minilst->cmds[i].args, minilst, minilst->cmds[i].fileout);
	k += checkforunset(minilst->cmds[i].cmd, minilst->cmds[i].args, minilst);
	if (ft_strcmp(minilst->cmds[i].cmd, "leaks") == 0)
	{
		k++;
		system("leaks minishell");
	}
	if (k == 0)
		executer(minilst, i, num); //EXECUTES THE NON BUILTINS
	else if(flag == 1) //FILTERS BETWEEN LAST CMDS AN MID EXECUTION CMDS
		exit(0);
}
