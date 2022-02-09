/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:39:15 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/09 01:51:13 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void checkeverything(char *line, t_minib *minilst)
{
	char	**auxline;

	auxline = ft_split(line, ' ');
	checkforexit(auxline);
	//checkforcd(auxline, envp, minilst)
	checkforenv(auxline, minilst->envp);
	if (ft_strcmp(auxline[0], "pwd") == 3)
	{
		if (auxline[1])
		{
			printf("minishell: too many arguments\n");
			return ;
		}
		printf("%s\n", minilst->pwd);
		return ;
	}
	//ft_parshe(line);
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
		checkeverything(line, &minilst);
	}
	return 0;
}