/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:29:20 by amanjon-          #+#    #+#             */
/*   Updated: 2024/04/16 13:01:35 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_signal_code = 0;

void	leaks(void)
{
	system("leaks -q minishell");
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

int	main(int argc, char **argv, char **envp)
{
	t_token	*token_list;
	t_scmd	*scmds_list;
	t_info	info;
	char	*line;

	info.envi = NULL;
	info.bin_paths = NULL;
	info.env_cpy = NULL;
	info.fl_exit = 0;
	token_list = NULL;
	scmds_list = NULL;
	line = NULL;
	ft_handle_env_execut(&info, argc, argv, envp);
	while (1)
	{
		if (loop(&info, token_list, scmds_list, line))
			break ;
	}
	free_array(info.env_cpy);
	ft_lstclear_ms(&(info.envi), &del_ms);
	atexit(leaks);
	exit (0);
}
