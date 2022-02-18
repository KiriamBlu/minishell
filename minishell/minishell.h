/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:39:38 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/18 15:30:18 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

//Header files
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>


typedef struct s_cmds 
{
	char	*args;
	int		type;
}	t_cmds;

typedef struct s_minib
{
	t_list	*envp;
	t_list	*exp;
	int		envindex;
	int		expindex;
	char	*pwd;
}	t_minib;

//MINISHELLSTRUCTURE

char	**getdonexp(char **envp, int i);
void	prepbasics(t_minib *minilst, char **envp);

//BUILTINS

void	checkforexit(char **line, t_minib *minilst);
void	checkforenv(char **line, t_list *envp);
void	checkforexport(char **line, t_minib *minilst);
void	checkforcd(char **line, t_minib *minilst);
void	*fuckeveryting(t_list *list);
void	checkforunset(char **line, t_minib *minilst);

//LEXER

void	ft_parshe(char *line);

//UTILS

int		getgoodpositionexp(t_list *list, char *add);
void	freeeverything(t_minib *minilst);
char	**createlstarray(t_list *lst, int index);
void	freemat(char **mat);
void	putinpos(t_list **list, int pos, void *newcontent);
void	delpos(t_list **list, int pos);
int 	isinexp(t_list *list, char *line);
char	*getlineinenv(t_list *list, int i);
t_list	*createarraylst(char **array);
int		getvariable(char *add, t_minib *minilst);
int		itsinenv(char *add, t_list *list);
int		getposinlst(t_list *list, char *line);
char	*getnamevariable(char *add);

//DEBUGGIN TOOLS

void	printlist(t_list *list);
void	printlistexp(t_list *list);

#endif
