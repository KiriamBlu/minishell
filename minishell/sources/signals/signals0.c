/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:15:25 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/03/03 15:58:16 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
 
 #include "../../minishell.h"

static void docontrolc(int signal)
{
	signal = 0;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}

void	inputsignal(void)
{
	signal(SIGINT, docontrolc);
	signal(SIGQUIT, SIG_IGN);
}

/*PARA LOS COMANDOS
	PAPI CHULO:
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	HIJI:
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
*/