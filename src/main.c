/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:29:20 by amanjon-          #+#    #+#             */
/*   Updated: 2023/10/26 11:06:42 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * This function disable chars printed by ctrl+c '^C'
 * @param	void
 * @return	void
*/
static void	ft_disable_ctrl_c_printing_chars(void)
{
	int rc;

	rc = tcgetattr(0, &g_info.termios);
	if (rc != 0)
	{
		perror("tcgetattr");
		exit (1);
	}
	g_info.termios.c_lflag &= ~ECHOCTL;
	rc = tcsetattr(0, 0, &g_info.termios);
	if (rc != 0)
	{
		perror("tcsetattr");
		exit(1);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_process	*process;
	char *line;
	int i;
	g_info.env = NULL;
	g_info.pwd = NULL;
	(void) argv;
	(void) env;
	
	process = NULL;
	line = NULL;
	i = 0;
	ft_disable_ctrl_c_printing_chars();
	if (argc != 1)
	{
		printf("enter only the executable ./minishell, thanks\n");
		return (1);
	}
	ft_copy_env(&g_info, env);
	// ft_get_env(&g_info, env);
	while (1)
	{
		ft_signals();
		line = readline("minishell-3.2$ ");
		if (line == NULL)
		{
			printf("minishell-3.2$  exit\n");
			exit (0);
		}
		ft_tokenize(&process, line);
		add_history(line);
		printf("line = %s\n", line);
		tcsetattr(0, 0, &g_info.termios);
	}
	printf("process->content = %s\n", process->content);
	free(line);
	return (0);
}
