/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:26:44 by amanjon-          #+#    #+#             */
/*   Updated: 2024/01/17 09:19:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_quit(void)
{
	struct sigaction act;
	
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

void	signal_reset_prompt(int signal)
{
	t_inf inf;
	(void) signal;
    
	if (signal == SIGINT)   // new if ();
	{
		inf.signal_code = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		printf("Signal code: %d\n", inf.signal_code);
	}
	else if (signal == SIGQUIT)	// new else if();
		SIG_IGN ;
}

void	signal_interrupt(void)
{
	struct sigaction act;

	signal_quit(); //new
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_reset_prompt;
	sigaction(SIGINT, &act, NULL);
}

void	signals(void)
{
	signal_interrupt();
	signal_quit();
}

// function nueva
void	signal_print_newline(int signal)
{
	(void)signal;
	rl_on_new_line();
}

// function nueva
void	set_signals_noninteractive(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_print_newline;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
