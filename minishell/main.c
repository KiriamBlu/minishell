#include "./libft/libft.h"
#include <stdlib.h>

typedef struct s_k
{
	char *key;
	char *value;

	struct s_k *next;	
} t_k;


char *expan( char *str, t_k *list )
{
	t_k *tmp;

	tmp = list;

	while ( tmp )
	{
		if ( ft_strncmp(str, tmp->key, ft_strlen(tmp->key)) )
			return ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	
	return( ft_strdup("") );
}

t_k *fillList()
{
	t_k *tmp = malloc(sizeof(t_k) );

	tmp->key = "$a";
	tmp->value = "HOLA";

	t_k *tmp2 = malloc(sizeof(t_k) );
	tmp2->key = "$b";
	tmp2->value = "mundo";

	t_k *tmp3 = malloc(sizeof(t_k) );
	tmp3->key = "$c";
	tmp3->value = "colombia";

	tmp->next = tmp2;
	tmp2->next = tmp3;
	tmp3->next = NULL;
	return tmp;
}

 int len_expan (char *str )
 {
	 int i = 1;
	 while ( str[i] )
	 {
		 if ( str[i] == ' ' || str[i] == '$' )
		 	break;
		 i++;
	 }

	 return i ;
	 
 }

char	*ft_strjoinmod(char *line, char c)
{
	char	*tmp;
	int		i = 0;
	int		j = 0;


	while (line[i])
		i++;
	tmp = (char *)malloc(i + 2);
	while (j < i)
	{
		tmp[j] = line[j];
		j++;
	}
	tmp[j] = c;
	tmp[j + 1] = 0;
	free(line);
	return (tmp);
}

char* reestruct( char * str, t_k *list )
{
	char *tmp = str;
	char *before;
	char *middle;

	char *tmp_aux;

	int i = 0;
	before = ft_strdup("");
	while (tmp[i])
	{
		// char *exp = ft_strchr(&tmp[i], '$');
		if ( tmp[i] != '$' )
		{
			before = ft_strjoinmod(before, tmp[i]);
			i++;

		}

		else 
		{
			char *exp = ft_substr(&tmp[i], 0, len_expan(&tmp[i]) );


		 	tmp_aux = expan(  exp , list );
	

			middle = ft_strjoin(before, tmp_aux);
				printf (" --> %s\n", middle);

			free(before);

			before = ft_strjoin(middle, &tmp[ i + ft_strlen(exp)] );
			i += ft_strlen(exp) ;
		}

	}
	return before;
	
}

int main ( int argc, char *argv[] )
{

	(void)argc;

	// printf("%s\n", argv[1] );
	t_k *list = fillList();
	printf("%s\n", reestruct("echo $a $b", list) );

}