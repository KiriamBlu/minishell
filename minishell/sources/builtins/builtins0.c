/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 22:20:03 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/08 23:50:20 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	checkforcd(char *line, char **envp, t_minib *minilst)
{
	char	*s;
	int		i[2];

	if (ft_strcmp(line, "cd") != 2)
		return	;

	if (find_env("PWD", envp) == -1)
	{
		minilst->pwd = getcwd(NULL, 0);
	}
}

void checkforexit(char **line)
{
	int		i;

	i = 0;
	if (ft_strcmp(line[i], "exit") == 4)
	{
		printf("exit\n");
		if (!line[1])
			exit(0);
		if(line[2]) //SALIDA EN CASO DE MAS DE DOS ARGS
		{
			printf("minishell: exit: too many arguments\n");
			return ;
		}
		i = -1;
		while(line[1][++i])
		{
			if(ft_isdigit(line[1][i]) != 1)
			{
				printf("minishell: exit: %s: numeric argument required\n", line[1]);
				break ;
			}
		}
		exit(ft_atoi(line[1]));
	}
}