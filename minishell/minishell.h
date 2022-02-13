/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:39:38 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/10 20:19:33 by jsanfeli         ###   ########.fr       */
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
	char	*pwd;
}	t_minib;

void	printlist(t_list *list);
t_list	*createarraylst(char **array, int index);
void	prepbasics(t_minib *minilst, char **envp);
void	checkforexit(char **line);
void	ft_parshe(char *line);
void	checkforenv(char **line, t_list *envp);
void	checkforexport(char **line, t_minib *minilst);
char	**getdonexp(char **envp, int i);
void	freemat(char **mat);
void	putinpos(t_list *list, int pos, void *newcontent);
void	delpos(t_list *list, int pos);
int		getposinlst(t_list *list, char *line);
char	*getlineinenv(t_list *list, int i);
t_list	*createarraylst(char **array, int index);
void	checkforcd(char **line, t_minib *minilst);
char	**createlstarray(t_list *lst, int index);

//DEBUGGIN TOOLS

void	printlist(t_list *list);

#endif
