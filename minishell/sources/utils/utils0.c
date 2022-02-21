
#include "../../minishell.h"

void	freemat(char **mat)
{
	int	i;

	i = -1;
	while (mat[++i])
		free(mat[i]);
	free(mat);
}

void checkfrontandback(t_list **list, int pos, void *newcontent)
{
	void *k;

	k = *list;
	if(pos == 0)
		ft_lstadd_front(list, ft_lstnew(newcontent));
	else
	{
		ft_lstadd_back(list, ft_lstnew(newcontent));
		*list = k;
	}
}

void putinpos(t_list **list, int pos, void *newcontent) //IF LEAKS HERE IN TMP
{
	int i;
	t_list *aux;
	void *kk;
	t_list *tmp;

	i = ft_lstsize(*list);
	if(pos == 0 || pos == i)
	{
		checkfrontandback(list, pos, newcontent);
		return  ;
	}
	i = 0;
	kk = *list;
	while(++i < pos)
		*list = (*list)->next;
	tmp = (*list)->next;
	aux = ft_lstnew(newcontent);
	(*list)->next = aux;
	aux->next = tmp;
	*list = kk;
}

void delpos(t_list **list, int pos)
{
	int i;
	t_list *aux;
	void *kk;

	if(pos == 0)
	{
		*list = fuckeveryting(*list);
		return ;
	}
	i = 0;
	kk = *list;
	while(++i < pos)
		*list = (*list)->next;
	aux = (*list)->next;
	(*list)->next = (*list)->next->next;
	aux->next = NULL;
	free(aux->content);
	free(aux);
	*list = kk;
}

int isinexp(t_list *list, char *line)
{
	int i;
	int j;

	j = ft_lstsize(list);
	i = 1;
	while(i < j)
	{
		if(!strcmp(list->content, line))
			return(-1);
		list = list->next;
		i++;
	}
	return(0);
}

int	getposinlst(t_list *list, char *line)	
{
	int i;
	int j;
	char *tmp;

	j = ft_lstsize(list);
	i = 0;
	while(i < j)
	{
		tmp = getnamevariable(list->content);
		if(!strcmp(tmp, line))
		{
			free(tmp);
			return(i);
		}
		list = list->next;
		i++;
	}
	free(tmp);
	return(-1);
}

