/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:26:44 by amanjon-          #+#    #+#             */
/*   Updated: 2024/02/20 17:36:07 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	signal_quit(void)
// {
// 	struct sigaction act;
	
// 	ft_memset(&act, 0, sizeof(act));
// 	act.sa_handler = SIG_IGN;
// 	sigaction(SIGQUIT, &act, NULL);
// }

// void	signal_reset_prompt(int signal)
// {
// 	(void) signal;
    
// 	if (signal == SIGINT)   // new if ();
// 	{
// 		g_signal_code = 130;
// 		printf("\n");
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// 	else if (signal == SIGQUIT)	// new else if();
// 		SIG_IGN ;
// }

// void	signal_interrupt(void)
// {
// 	struct sigaction act;

// 	signal_quit(); //new
// 	ft_memset(&act, 0, sizeof(act));
// 	act.sa_handler = &signal_reset_prompt;
// 	sigaction(SIGINT, &act, NULL);
// }

// void	signals(void)
// {
// 	signal_interrupt();
// 	signal_quit();
// }

// // function nueva
// void	signal_print_newline(int signal)
// {
// 	(void)signal;
// 	rl_on_new_line();
// }

// // function nueva
// void	set_signals_noninteractive(void)
// {
// 	struct sigaction	act;

// 	ft_memset(&act, 0, sizeof(act));
// 	act.sa_handler = &signal_print_newline;
// 	sigaction(SIGINT, &act, NULL);
// 	sigaction(SIGQUIT, &act, NULL);
// }


//VITI
void	ft_signal_quit(void)
{
	struct sigaction act;
	
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

void	ft_signal_reset_prompt(int signal)
{
	(void) signal;
	// g_signal_code = 130;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_signal_interrupt(void)
{
	struct sigaction act;

	memset(&act, 0, sizeof(act));
	act.sa_handler = &ft_signal_reset_prompt;
	sigaction(SIGINT, &act, NULL);
}

void	ft_signals(void)
{
	ft_signal_interrupt();
	ft_signal_quit();
}

// MATEO

// void	ft_ignore_sigquit(void)
// {
// 	struct sigaction	act;

// 	ft_memset(&act, 0, sizeof(act));
// 	act.sa_handler = SIG_IGN;
// 	sigaction(SIGQUIT, &act, NULL);
// }

// void	ft_signal_reset_prompt(int signal)
// {
// 	if (signal == SIGINT)
// 	{
// 		(void)signal;
// 		// g_info.last_code = 130;
// 		printf("\n");
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// 	else if (signal == SIGQUIT)
// 		ft_ignore_sigquit();
// 		// SIG_IGN ;
// }

// void	ft_signal_print_newline(int signal)
// {
// 	(void)signal;
// 	rl_on_new_line();
// }

// void	ft_signals(void)
// {
// 	struct sigaction	act;

// 	ft_ignore_sigquit();
// 	ft_memset(&act, 0, sizeof(act));
// 	act.sa_handler = &ft_signal_reset_prompt;
// 	sigaction(SIGINT, &act, NULL);
// }

// void	ft_set_signals_noninteractive(void)
// {
// 	struct sigaction	act;

// 	ft_memset(&act, 0, sizeof(act));
// 	act.sa_handler = &ft_signal_print_newline;
// 	sigaction(SIGINT, &act, NULL);
// 	sigaction(SIGQUIT, &act, NULL);
// }
