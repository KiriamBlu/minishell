/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 18:06:16 by jporta            #+#    #+#             */
/*   Updated: 2021/12/21 15:57:14 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_errorpipex(int index)
{
	if (index == 0)
	{
		ft_putstr_fd("Error dude\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	simba(char **argv, char **envp, int i)
{
	int		pid;
	int		fd[2];

	if (pipe(fd) == -1)
		ft_errorpipex(0);
	pid = fork();
	if (pid == -1)
		ft_errorpipex(0);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(argv, envp, i);
	}
	else
		finish(fd[1], fd[0], pid);
}

int	heredocexe(t_aux *aux, char **argv, int argc)
{
	pid_t	pid;
	int		fd[2];
	char	*line;
	char	*tmp;

	tmp = ft_strjoin(argv[2], "\n");
	aux->fileout = open_file(argv[argc - 1], 2);
	if (pipe(fd) == -1)
		ft_errorpipex(0);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		while (get_next_line(&line))
		{
			if (ft_strcmp(line, tmp) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
		}
		free(tmp);
	}
	else
		finish(fd[1], fd[0], pid);
	return (3);
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_aux	*aux;

	if (argc >= 5)
	{
		aux = malloc(sizeof(t_aux));
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			if (argc < 6)
				ft_errorpipex(0);
			i = heredocexe(aux, argv, argc);
		}
		else
		{
			i = 2;
			aux->fileout = open_file(argv[argc - 1], 0);
			aux->filein = open_file(argv[1], 1);
			dup2(aux->filein, STDIN_FILENO);
		}
		while (i < argc - 2)
			simba(argv, envp, i++);
		dup2(aux->fileout, STDOUT_FILENO);
		execute(argv, envp, (argc - 2));
	}
	ft_errorpipex(0);
}
