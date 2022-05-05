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

# define ALIEN  "👽"
# define SKULL	"🦠"
# define FLAME	"🔥"
# define PATH_TO_TMP	"/tmp/"
# define BLUE_BOLD "\e[1;34m"
# define GREEN_BOLD "\e[1;32m"
# define MAG_BOLD "\e[1;35m"
# define RED_BOLD "\e[1;31m"
# define UNSET "\033[0m"
# define CYAN "\e[0;36m"

typedef struct s_cmds 
{
	char	*cmd;
	char	*args;
	int		filein;
	int 	fileout;
	int		in_fd;
}	t_cmds;

typedef struct s_minib
{
	t_cmds	*cmds;
	t_list	*envp;
	t_list	*exp;
	int		envindex;
	int		expindex;
	int 	cmdnum;
	int		shlvl;
	char	*lastcmd;
	int		cmdstatus;
	char	*pwd;
	char	*promt;
}	t_minib;


//MINISHELLSTRUCTURE

char	**getdonexp(char **envp, int i);
void	prepbasics(t_minib *minilst, char **envp);

//BUILTINS

int	checkforexit(char *cmd, char *arg, t_minib *minilst); //HECHA LA GESTION DE LAS REDIRECCIONES
int	checkforenv(char *cmd,  t_list *envp, int fileout, int *status); //GESTIONADAS LAS REDIRECCIONES
int	checkforexport(char *cmd, char *arg, t_minib *minilst, int fileout); //GESTIONADAS LAS REDIRECCIONES
int	checkforcd(char *cmd, char *arg, t_minib *minilst, int fileout); //GESTIONADAS LAS REDIRECCIONES
int	checkforunset(char *cmd, char *arg, t_minib *minilst);//GESTIONADAS LAS REDIRECCIONES
int checkforecho(char *cmd, char *arg, int fileout, int *status);//GESTIONADAS LAS REDIRECCIONES

//LEXER

int		morfeo(t_cmds *com, char **line);
char	*expander(char *line, t_minib *minilst);
char	**lexer(char *expanded);

//SIGNALS

void	inputsignal(void);
void	rl_replace_line (const char *text, int clear_undo);

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
void	*fuckeveryting(t_list *list);
int		getvariable(char *add, t_list *list);
int		itsinenv(char *add, t_list *list);
int		getposinlst(t_list *list, char *line);
char	*getnamevariable(char *add);
int		checkadd(char *add);
int		num_matrix(char **matrix);
int		count_c(char *str, char c); //cuenta pipes validos
void	freecmds(t_minib *minilst);
char	*getaddedexp(char *add);
char	*freezerjoin(char *s1, char *s2);
char	*dopromt(t_minib *minilst);
char	*argsdone(char *arg);
char	*comparse(char *add);

//DEBUGGIN TOOLS

void	printlist(t_list *list, int fileout);
void	printlistexp(t_list *list, int fileout);
void	errorprintf(char *str, int *status);

//EXECUTER

void	executer(t_minib *minilst, int i, int num);
char	*path(char *cmd, char **envp);
void	ft_errorpipex(int index);
void	simba(t_minib *minilst, int i );
void	ejecucion(t_minib *minilst, int i, int num);
void	finish_ejecucion(t_minib *minilst, int i, int num);

#endif
