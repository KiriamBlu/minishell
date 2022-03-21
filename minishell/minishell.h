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


typedef struct s_lexer
{
	char	*line;
	char	**dolar;
	char	**expandenv;

} t_lexer;

typedef struct s_cmds 
{
	char	*cmd;
	char	*args;
	int		type;
}	t_cmds;

typedef struct s_minib
{
	t_cmds	*cmds;
	t_lexer	*lexer;
	t_list	*envp;
	t_list	*exp;
	int		envindex;
	int		expindex;
	int 	cmdnum;
	char	*pwd;
}	t_minib;




//MINISHELLSTRUCTURE

char	**getdonexp(char **envp, int i);
void	prepbasics(t_minib *minilst, char **envp);

//BUILTINS

void	checkforexit(char *cmd, char *arg, t_minib *minilst);
void	checkforenv(char *cmd, char *arg, t_list *envp);
void	checkforexport(char *cmd, char *arg, t_minib *minilst);
void	checkforcd(char *cmd, char *arg, t_minib *minilst);
void	checkforunset(char *cmd, char *arg, t_minib *minilst);
void 	checkforecho(char *cmd, char *arg);

//LEXER

char	**ft_prepare(char *line);
void	morfeo(t_cmds *com, char **line);
char	**lexer(t_list *list, char *line, t_lexer *lexer);
char	*ft_prueba(char *line, t_list *list);
char	**lexier(char *expanded);

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

//DEBUGGIN TOOLS

void	printlist(t_list *list);
void	printlistexp(t_list *list);

#endif
