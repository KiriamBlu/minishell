/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:18:32 by jporta            #+#    #+#             */
/*   Updated: 2022/06/01 18:47:45 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	programe_reading(t_minib *minilst, int i);

int	main(int argc, const char **argv, char **envp)
{
	t_minib	minilst;
	int		i;

	(void)argv;
	if (argc != 1)
		exit(0);
	i = 0;
	prepbasics(&minilst, envp);
	minilst.promt = dopromt(&minilst);
	while (1)
		programe_reading(&minilst, i);
	free(minilst.promt);
	return (0);
}

void	programe_reading(t_minib *minilst, int i)
{
	char	*line;
	char	*promt;

	inputsignal();
	promt = ft_strdup(minilst->promt);
	line = readline(promt);
	if (!line)
	{
		printf("exit\n");
		if (i > 0)
			freecmds(minilst);
		exit(0);
	}
	if (ft_strlen(line) != 0 && checkforspaces(line) != 0 && line)
	{
		add_history(line);
		checkeverything(line, minilst);
		freecmds(minilst);
		i++;
	}
	free(line);
	free(promt);
}