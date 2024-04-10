/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:26:44 by amanjon-          #+#    #+#             */
/*   Updated: 2024/04/08 11:05:54 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * --------- RESET PROMPT ---------
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
 * The signation function is used to set this configuration for the
 * SIGINT signal.
 * @param	void
 * @return	void
*/
void	ft_signal_interrupt(void)
{
	struct sigaction	act;

	ft_signal_quit();
	memset(&act, 0, sizeof(act));
	act.sa_handler = &ft_signal_reset_prompt;
	sigaction(SIGINT, &act, NULL);
}

/**
 * Prints a newline for noninteractive signal handling.
*/
void	ft_signal_newline(int signal)
{
	(void)signal;
	rl_on_new_line();
}

/**
 * Sets the behavior in response to SIGINT (ctrl -c) and SIGQUIT (ctrl -\).
 * Used when minishell is in noninteractive mode, meaning it is not awaiting
 * user input. For example, when a command is running (i.e. cat), minishell
 * should not react to SIGINT and SIGQUIT because only the running process (cat)
 * needs to react to those signals.
*/
void	ft_signals_noninteractive(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &ft_signal_newline;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

/**
 * --------- CTRL + D - CTRL + \  ---------
 * You declare a structure called "act" that will receive the signal.
 * All elements of the struct are initialized to 0 with the memset function.
 * When SIGQUIT signal is received it will be ignored
 * The signation function is used to set this configuration for the
 * SIGQUIT signal.
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
