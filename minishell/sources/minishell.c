/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:39:15 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/10 14:51:07 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void checkeverything(char *line, t_minib *minilst)
{
	char	**auxline;

	auxline = ft_split(line, ' ');
	if(!auxline[0])
		return ;
	checkforexit(auxline);
	checkforcd(auxline, minilst->envp, minilst);
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
	checkforexport(auxline, minilst);
	//ft_parshe(line);
	return ;
}

void prepbasics(t_minib *minilst, char **envp)
{
	int i;

	i = 0;
	minilst->pwd = getcwd(NULL, 0);
	while(envp[i])
		i++;
	minilst->envindex = i;
	minilst->envp = malloc(sizeof(char *) * minilst->envindex);
	i = -1;
	while(envp[++i])
		minilst->envp[i] = ft_strdup(envp[i]);
	minilst->exp = getdonexp(envp, minilst);
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
	prepbasics(&minilst, envp);
	while(1)
	{
		line = readline("minishell> ");
		add_history(line);
		checkeverything(line, &minilst);
		free(line);
	}
	return 0;
}