/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:26:44 by amanjon-          #+#    #+#             */
/*   Updated: 2024/03/28 10:39:24 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * --------- CTRL + D - CTRL + \  ---------
 * You declare a structure called "act" that will receive the signal.
 * All elements of the struct are initialized to 0 with the memset function.
 * When SIGQUIT signal is received it will be ignored
 * The signation function is used to set this configuration for the SIGQUIT signal.
 * @param	void
 * @return	void
*/
void	ft_signal_quit(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

/**
 * --------- RESET PROMT ---------
 * The value 130 represents termination by Ctrl + C, which sends
 * the SIGINT signal.
 * rl_on_new_line: system function, that the cursor has moved to a new line
 * rl_replace_line: replaces the current content with an empty string and
 * the second argument 0 indicates that editing history will not be saved.
 * rl_redisplay: redisplays the updated input line on the screen
 * @param	int signal
 * @return	void
*/
void	ft_signal_reset_prompt(int signal)
{
	(void) signal;
	g_signal_code = 130;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * --------- CTRL + C ---------
 * You declare a structure called "act", that will receive the content of a
 * "ft_signal_reset_prompt" function to display a new prompt in the terminal.
 * All elements of the struct are initialized to 0 with the memset function.
 * We assign the address of the function 'ft_signal_reset_prompt', so that
 * this function is executed with the SIGINT signal.
 * The signation function is used to set this configuration for the SIGINT signal.
 * @param	void
 * @return	void
*/
void	ft_signal_interrupt(void)
{
	struct sigaction	act;

	memset(&act, 0, sizeof(act));
	act.sa_handler = &ft_signal_reset_prompt;
	sigaction(SIGINT, &act, NULL);
}

/**
 * Control + "D": close the terminal.
 * Control + "C": prints a new entry on a new line.
 * Control + "\": does nothing.
 * @param	void
 * @return	void
*/
void	ft_signals(void)
{
	ft_signal_interrupt();
	ft_signal_quit();
}
