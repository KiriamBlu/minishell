/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 00:21:27 by jporta            #+#    #+#             */
/*   Updated: 2022/04/12 17:50:11 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int countdollars(char *line)
{
	int a;
	int k;

	a = 0;
	k = 0;
	while (line[a])
	{
		if(line[a] == '\'')
			while(line[++a] != '\'')
				;
		else if (line[a] == '$')
			k++;
		a++;
	}
	return (k);
}

 int len_expan (char *str)
 {
	 int i = 1;
	 while (str[i])
	 {
		 if (str[i] == ' ' || str[i] == '$' || str[i] == '"')
		 	break;
		 i++;
	 }

	 return (i);
	 
 }

int ft_getlenname(char *line, int start)//mirar si start es == a dollar o el anterior
{
	int i;

	i = start + 1;
	if(line[i] == '?')
		return(2);
	while(ft_isalnum(line[i]) == 1 && line[i + 1] != ' ' && line[i + 1] != '$' && line[i + 1] != '"')
		i++;
	return(i - start);
}

char *expanddollar(char *name, t_list *list)
{
	char	*expand;
	int		check;

	if(name[0] == '?')
	{
		free(name);
		return("$");
	}
	check = getposinlst(list, name) + 1;
	if(check == 0)
		return(" ");
	expand = getlineinenv(list, check);
	return(ft_substr(expand, ft_strlen(name) + 1, ft_strlen(expand)));
}

char *ft_prueba(char *line, t_list *list) //NAME[0] = FULL; NAME[1] = TMP; NAME[2] = AUX; NAME[3] = NAME
{
	int	i;
	int	a;
	int k;
	char *name[4];
	char *aux;
	
	i = 0;
	a = 0;
	k = countdollars(line);
	if(k == 0)
		return(ft_strdup(line));
	name[1] = ft_strdup(line); //GUARDAR EN LA TMP LA LINEA PARA EMPEZAR A TRABAJAR CON UNA LINEA CAMBIANTE
	while (k > 0)
	{
		while (line[a] != '$')
		{
			if(line[a] == '\'')
				while(line[++a] != '\'')
					;
			a++;
		}
		aux = ft_substr(line, i, a - i); //GUARDAS DESE EL PUUNTO DONDE VAS A TRABAJAR EN AUX PARA AÑADIR DESDE AHI LA EXPANSIÓN
		name[3] = ft_substr(line, a + 1, ft_getlenname(line, a)); //OBTIENES Y ALMACENAS EL NOMBRE DE LA VARIABLE A SER EXPANDIDA
		name[2] = freezerjoin(aux, expanddollar(name[3], list)); //UNES LA EXPANSION DESDE EL TAMAÑO DE REYENO HASTA EL FINAL DE AUX
		name[0] = freezerjoin(name[0], name[2]);//AQUIIIIIIIIIII EL LEAK EN NAME[0], necesitaas auxiliar
		a += ft_strlen(name[3]) + 1; //GUARDAS LA POSICION DESDE DONDE CUENTAS
		free(name[1]);
		free(name[3]);
		name[1] = ft_substr(line, a, name[0] - line); //EN LA TEMPORAL GUARDAS EL FINAL
		i = a;
		k--;
	}
	name[0] = freezerjoin(name[0], name[1]); //EL RESTO DE LA FRASE UNA VEZ NO QUEDAN '$'
	//system("leaks minishell");
	return (name[0]);
}
