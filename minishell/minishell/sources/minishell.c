/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:39:15 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/17 19:07:32 by jporta           ###   ########.fr       */
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
	minilst->envp = createarraylst(envp);
	minilst->exp = createarraylst(aux);
	minilst->envindex = i;
	minilst->expindex = i;
	freemat(aux);
}

char	*expansion(t_list *list, char *line)
{
	char *aux;
	
	free(line);;
	return(aux);
}


void checkeverything(char *line, t_minib *minilst)
{
	char	**auxline;

	auxline = ft_split(line, ' ');
	if(!auxline[0])
		return ;
	//ft_parshe(line);
	checkforexit(auxline, minilst);
	checkforcd(auxline, minilst);
	checkforenv(auxline, minilst->envp);
	if (ft_strncmp(auxline[0], "pwd", ft_strlen(auxline[0])) == 0)
	{
		if (auxline[1])
		{
			printf("minishell: too many arguments\n");
			freemat(auxline);
			return ;
		}
		free(minilst->pwd);
		minilst->pwd = getcwd(NULL, 0);
		printf("%s\n", minilst->pwd);
		freemat(auxline);
		return ;
	}
	checkforexport(auxline, minilst);
	checkforunset(auxline, minilst);
	freemat(auxline);
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