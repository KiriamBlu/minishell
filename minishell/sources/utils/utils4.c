#include "../../minishell.h"


void errorprintf(char *str, int *status)
{
	printf("%s", str);
	*status = 1;
}

/*void	heredocexe(t_aux *aux, char **argv, int argc)
{
	pid_t	pid;
	int		fd[2];
	char	*line;
	char	*tmp;

	tmp = ft_strjoin(argv[2], "\n");
	minilst->fileout = open(aux, O_WRONLY | O_CREAT | O_APPEND, 0666);
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
	return ;*/