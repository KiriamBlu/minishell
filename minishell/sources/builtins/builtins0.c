/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 22:20:03 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/08 22:33:30 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void checkforexit(char *line)
{
	char	**pcsline; //PROCESSED LINE, SE UTILIZA EN EL CASO DE QUE LLEGUEN MAS DE UN ARGUMENTO EN EL EXIT
	int		i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\n' || line[i] == '\t' \
			|| line[i] == '\f' || line[i] == '\v' || line[i] == '\r')
		i++;
	if (ft_strcmp(&line[i], "exit") == 4)
	{
		printf("exit\n");
		pcsline = ft_split(line, ' ');
		if (!pcsline[1])
			exit(0);
		if(pcsline[2]) //SALIDA EN CASO DE MAS DE DOS ARGS
		{
			printf("minishell: exit: too many arguments\n");
			freemat(pcsline);
			return ;
		}
		i = -1;
		while(pcsline[1][++i])
			if(ft_isdigit(pcsline[1][i]) != 1)
				printf("minishell: exit: %s: numeric argument required\n", pcsline[1]);
		exit(ft_atoi(pcsline[1]));
	}
}