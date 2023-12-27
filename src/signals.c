/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:26:44 by amanjon-          #+#    #+#             */
/*   Updated: 2023/12/27 13:35:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_signal_quit(void)
{
	struct sigaction act;
	
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

void	ft_signal_reset_prompt(int signal)
{
	// t_inf inf;
	(void) signal;
    
	// inf.signal_code = 130;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	// printf("Signal code: %d\n", inf.signal_code);
}

void	ft_signal_interrupt(void)
{
	struct sigaction act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &ft_signal_reset_prompt;
	sigaction(SIGINT, &act, NULL);
}

void	ft_signals(void)
{
	ft_signal_interrupt();
	ft_signal_quit();
}
