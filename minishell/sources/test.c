/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:39:15 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/08 18:14:24 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void checkforexit(char *line)
{
	if (ft_strcmp(lol, "exit") == 4)
	{
		printf("%s\n", lol);
		if(ft_strcmp(lol, "exit") == 4 && lol[4] == '\0')
		{
			free(lol);
			exit(0);
		}
	}
}

void checkeverything(char *line, char **envp)
{
	checkforexit(cmd, envp);
}

int main(int argc, const char **argv, char **envp)
{
	char *line;

	argv = NULL;
	if(argc != 1)
		exit(0);
	while(1)
	{
		line = readline("minishell> ");
		add_history(line);
		checkforeverything(line, evnp)
		free(lol);
	}
	return 0;
}