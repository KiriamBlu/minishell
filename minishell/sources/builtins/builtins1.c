/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 05:19:23 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/04/12 16:28:17 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char **getdonexp(char **envp, int i)
{
	char	**aux;
	int		j;
	int		k;
	int		count;

	aux = ft_calloc(sizeof(char *), i + 1);
	k = -1;
	while(envp[++k])
	{
		count = 0;
		j = -1;
		while (envp[++j])
		{
			if (ft_strncmp(envp[k], envp[j], ft_strlen(envp[j]) + 1) > 0)
				count++;
		}
		aux[count] = getaddedexp(envp[k]);
	}
	return(aux);
}

char *do_real_arg(char *add)
{
	int i;
	char *final;
	char *second;
	char *new;
	char *aux;

	i = 0;
	if(!ft_strchr(add, '"'))
		return(ft_strdup(add));
	final = getnamevariable(add);
	second = ft_strjoin(final, "=");
	free(final);
	aux = ft_strdup(ft_strchr(add, '='));
	while(aux[i] != '"')
		i++;
	i++;
	while(aux[i] != '"')
		i++;
	i -= 2;
	final = ft_substr(aux, 2, i);
	free(aux);
	new = ft_strjoin(second, final);
	free(second);
	free(final);
	return(new);
}

void getaddexp(char *add, t_minib *minilst)
{
	char *tmp;
	char *aux;
	int i;

	i = getvariable(add, minilst->envp);
	if (itsinenv(add, minilst->exp) != -1)
	{
		if (ft_strchr(add, '='))
		{
			tmp = do_real_arg(add);
			putinpos(&minilst->envp, ft_lstsize(minilst->envp), ft_strdup(tmp));
			putinpos(&minilst->exp, getgoodpositionexp(minilst->exp, add), getaddedexp(tmp));
			free(tmp);
		}
		else
			putinpos(&minilst->exp, getgoodpositionexp(minilst->exp, add), ft_strdup(add));
	}
	else
	{
		tmp = getnamevariable(add);
		aux = do_real_arg(add);
		if(itsinenv(add, minilst->envp) == -1 && ft_strchr(add, '='))
			delpos(&minilst->envp, i - 1);
		if(ft_strchr(add, '='))
			putinpos(&minilst->envp, i - 1, ft_strdup(aux));
		i = getposinlst(minilst->exp, tmp);
		if(itsinenv(add, minilst->envp) == -1 && ft_strchr(add, '='))
		{
			delpos(&minilst->exp, i);
			putinpos(&minilst->exp, i, getaddedexp(aux));
		}
		free(tmp);
		free(aux);
	}
}

int checkadd(char *add)
{
	char *aux;
	int i;

	i = 0;
	if(add[0] == '=' || ft_isdigit(add[0]) == 1)
		return(-1);
	aux = getnamevariable(add);
	while(aux[i])
	{
		if(ft_isalnum(aux[i]) == 0 && aux[i] != '_')
		{
			free(aux);
			return(-1);
		}
		i++;
	}
	free(aux);
	return(0);
}

char **exportarg(char *cmd)
{
	int i;
	int a;
	int numcom;
	int status;
	char **comands;

	numcom = count_c(cmd, ' ');
	comands = malloc(sizeof(char *) * numcom + 1);
	i = 0;
	a = 0;
	status = 0;
	while(cmd[i] == ' ')
		i++;
	while(numcom > 0)
	{
		while(cmd[i] != ' ' && cmd[i])
		{
			if (cmd[i] == '\'')
				while(cmd[++i] != '\'')
					;
			if (cmd[i] == '"')
				while(cmd[++i] != '"')
					;
			i++;
		}
		comands[status] = ft_substr(cmd, a, i - a);
		i += 1;
		a = i;
		status++;
		numcom--;
	}
	comands[numcom - 1] = 0;
	return(comands);
}

void checkforexport(char *cmd, char *arg, t_minib *minilst)
{
	int i;
	char **args;

	i = -1;
	if (strcmp(cmd, "export") != 0)
		return	;
	if(ft_strlen(arg) == 0)
	{
		printlistexp(minilst->exp);
		return ;
	}
	args = exportarg(arg); // ANADIR LA SEPARACIÓN DE LOS ARGUMENTOS POR ("")
	while(args[++i])
	{
		if(checkadd(args[i]) == -1)
			printf("minishell: export: %s: not a valid identifier\n", args[1]);
		getaddexp(args[i], minilst);
	}
	freemat(args);
}

void checkforunset(char *cmd, char *arg, t_minib *minilst)
{
	int i;
	int j;
	char **args;

	j = -1;
	if (strcmp(cmd, "unset") != 0)
		return	;
	args = ft_split(arg, ' ');
	if(!args[0])
		return ;
	while(args[++j])
	{
		if(checkadd(args[j]) == -1)
			printf("minishell: unset: %s: not a valid identifier\n", args[1]);
		i = getposinlst(minilst->envp, args[j]);
		if(i != -1)
		{
			minilst->envindex--;
			delpos(&minilst->envp, i);
		}
		i = getposinlst(minilst->exp, args[j]);
		if(i != -1)
		{
			minilst->expindex--;
			delpos(&minilst->exp, i);
		}
	}
	freemat(args);
}
