/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:39:15 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/09 00:01:20 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void checkeverything(char *line, char **envp, t_minib *minilst)
{
	char	**auxline;

	auxline = ft_split(line, ' ');
	checkforexit(auxline);
	//checkforcd(auxline, envp, minilst)
	if(ft_strcmp(&line[0], "pwd") == 3)
	{
		printf("%s\n", minilst->pwd);
		return ;
	}
	ft_parshe(line);
}

void leaks(void)
{
	system("leaks minishell");
}

int main(int argc, const char **argv, char **envp)
{
	t_minib	minilst;
	char *line;

	//atexit(leaks);
	argv = NULL;
	if(argc != 1)
		exit(0);
	while(1)
	{
		minilst.pwd = getcwd(NULL, 0);
		minilst.envp = envp;
		line = readline("minishell> ");
		add_history(line);
		checkeverything(line, envp, &minilst);
	}
	return 0;
}