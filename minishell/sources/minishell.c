/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:39:15 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/10 20:19:57 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void prepbasics(t_minib *minilst, char **envp)
{
	int i;
	char **aux;

	minilst->pwd = getcwd(NULL, 0);
	i = 0;
	while(envp[i])
		i++;
	aux = getdonexp(envp, i);
	minilst->envindex = i;
	minilst->envp = createarraylst(envp, minilst->envindex);
	minilst->exp = createarraylst(aux, minilst->envindex);
	free(aux);
}

void checkeverything(char *line, t_minib *minilst)
{
	char	**auxline;

	auxline = ft_split(line, ' ');
	if(!auxline[0])
		return ;
	checkforexit(auxline);
	checkforcd(auxline, minilst);
	checkforenv(auxline, minilst->envp);
	if (ft_strcmp(auxline[0], "pwd") == 3)
	{
		if (auxline[1])
		{
			printf("minishell: too many arguments\n");
			return ;
		}
		minilst->pwd = getcwd(NULL, 0);
		printf("%s\n", minilst->pwd);
		return ;
	}
	checkforexport(auxline, minilst);
	//ft_parshe(line);
	return ;
}

int main(int argc, const char **argv, char **envp)
{
	t_minib	minilst;
	char *line;

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