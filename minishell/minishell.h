/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:39:38 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/08 23:33:08 by jsanfeli         ###   ########.fr       */
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

typedef struct s_minib
{
	char	**envp;
	char	*pwd;
}	t_minib;

void	freemat(char **mat);
void	checkforexit(char **line);
int		find_env(char *name, char **env);
void	checkforcd(char *str, char **envp, t_minib *minilst);
void	rebuild_pwd(void);

#endif
