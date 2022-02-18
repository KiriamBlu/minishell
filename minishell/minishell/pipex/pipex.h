/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 04:05:59 by jporta            #+#    #+#             */
/*   Updated: 2021/12/20 18:29:21 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft/libft.h"

typedef struct s_aux
{
	int	filein;
	int	fileout;
}		t_aux;

void	execute(char **argv, char **envp, int num);
char	*path(char *cmd, char **envp);
void	ft_errorpipex(int index);
int		open_file(char *argv, int i);
int		get_next_line(char **line);
void	finish(int fd1, int fd0, int pid);

#endif
