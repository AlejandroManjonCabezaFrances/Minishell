/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:29:20 by amanjon-          #+#    #+#             */
/*   Updated: 2024/04/10 11:28:38 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_signal_code = 0;

// void	leaks(void)
// {
// 	system("leaks -q minishell");
// }

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
		if (loop(&info, token_list, scmds_list, line) || info.fl_exit == 1)
			break ;
	system("leaks -q minishell");
	}
	free(line);
	free_array(info.env_cpy);
	ft_lstclear_ms(&(info.envi), &del_ms);
	// atexit(leaks);
	return (0);
}
