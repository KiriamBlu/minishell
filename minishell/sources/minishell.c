/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:39:15 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/08 22:34:33 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void checkeverything(char *line, char **envp)
{
	checkforexit(line);
}

void leaks(void)
{
	system("leaks minishell");
}

int main(int argc, const char **argv, char **envp)
{
	char *line;

	//atexit(leaks);
	argv = NULL;
	if(argc != 1)
		exit(0);
	while(1)
	{
		line = readline("minishell> ");
		add_history(line);
		checkeverything(line, envp);
	}
	return 0;
}