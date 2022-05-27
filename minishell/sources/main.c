/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:18:32 by jporta            #+#    #+#             */
/*   Updated: 2022/05/27 18:18:43 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, const char **argv, char **envp)
{
	t_minib	minilst;
	char	*line;
	char	*promt;
	int		i;

	(void)argv;
	if (argc != 1)
		exit(0);
	i = 0;
	prepbasics(&minilst, envp);
	minilst.promt = dopromt(&minilst);
	while (1)
	{
		inputsignal();
		promt = ft_strdup(minilst.promt);
		line = readline(promt);
		if (!line)
		{
			printf("exit\n");
			if (i > 0)
				freecmds(&minilst);
			exit(0);
		}
		if (ft_strlen(line) != 0 && checkforspaces(line) != 0 && line)
		{
			add_history(line);
			checkeverything(line, &minilst);
			freecmds(&minilst);
			i++;
		}
		free(line);
		free(promt);
	}
	free(minilst.promt);
	return (0);
}
