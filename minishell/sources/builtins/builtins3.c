/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 05:19:23 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/06/01 22:39:59 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	unsetter(char *tmp, t_minib *minilst, char **args);

int	checkforunset(char *cmd, char *arg, t_minib *minilst)
{
	int		j;
	char	**args;
	char	*tmp;

	j = -1;
	if (!cmd || ft_strcmp(cmd, "unset") != 0)
		return (0);
	args = ft_split(arg, ' ');
	if (!args[0])
		return (1);
	while (args[++j])
	{
		tmp = comparse(args[j]);
		unsetter(tmp, minilst, args);
		free(tmp);
	}
	freemat(args);
	g_cmd_status = 0;
	return (1);
}

int	unsetter(char *tmp, t_minib *minilst, char **args)
{
	int	i;

	if (checkadd(tmp) == -1)
	{
		printf("minishell: unset: %s: not a valid identifier\n", args[0]);
		return (0);
	}
	i = getposinlst(minilst->envp, tmp);
	if (i != -1)
	{
		minilst->envindex--;
		delpos(&minilst->envp, i);
	}
	i = getposinlst(minilst->exp, tmp);
	if (i != -1)
	{
		minilst->expindex--;
		delpos(&minilst->exp, i);
	}
	return (0);
}

int	checkadd(char *add)
{
	char	*aux;
	int		i;

	i = 0;
	if (add[0] == '=' || ft_isdigit(add[0]) == 1)
		return (-1);
	aux = getnamevariable(add);
	while (aux[i])
	{
		if (ft_isalnum(aux[i]) == 0 && aux[i] != '_')
		{
			free(aux);
			return (-1);
		}
		i++;
	}
	free(aux);
	return (0);
}

char	**exportarg(char *cmd)
{
	int		i;
	int		a;
	int		numcom;
	int		status;
	char	**comands;

	numcom = count_c(cmd, ' ');
	comands = ft_calloc(sizeof(char *), numcom + 1);
	i = 0;
	a = 0;
	status = 0;
	while (cmd[i] == ' ')
		i++;
	while (numcom > 0)
	{
		i = helpecho(cmd, i);
		comands[status] = ft_substr(cmd, a, i - a);
		i += 1;
		a = i;
		status++;
		numcom--;
	}
	return (comands);
}

char	*do_real_arg(char *add)
{
	int		i;
	char	*final;
	char	*second;
	char	*new;
	char	*aux;

	i = 0;
	if (!ft_strchr(add, '"'))
		return (ft_strdup(add));
	final = getnamevariable(add);
	second = ft_strjoin(final, "=");
	free(final);
	aux = ft_strdup(ft_strchr(add, '='));
	while (aux[i] != '"')
		i++;
	i++;
	while (aux[i] != '"')
		i++;
	i -= 2;
	final = ft_substr(aux, 2, i);
	free(aux);
	new = ft_strjoin(second, final);
	free(second);
	free(final);
	return (new);
}
