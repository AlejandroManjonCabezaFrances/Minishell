/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:29:20 by amanjon-          #+#    #+#             */
/*   Updated: 2024/03/07 11:23:45 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int g_signal_code = 0;
int	exit_status = 0;

void	shell_operation(char *line, t_token *list, t_scmd *scmds, t_info info)
{
	int	err;

	err = lexer(&list, line);
	add_history(line);
	if (err != 1)
		panic(err, NULL, NULL);
	if (err == 1)
	{
		err = parser(&list, &scmds, &info);
		if (err != 1)
			panic(err, NULL, NULL);
		err = executer(&scmds, &info);
		if (err != 1)
			panic(err, NULL, NULL);
	}
	free(line);
	ms_lstclear(&list);
	ms_close_fds(&scmds);
	ms_cmdclear(&scmds);
}

int	check_argc(int argc)
{
	if (argc != 1)
	{
		printf("enter only the executable ./minishell, thanks\n");
		return (1);
	}
	return (0);
}

/**
 * Structure is initialized for signals
 * @param	t_inf *inf
 * @return	void
*/
void	init_struct(t_env *envi, t_inf *inf)
{
	envi->env_n = NULL; 
	inf->cwd = NULL;
}
/**
 * This function disable chars printed by ctrl+c '^C'
 * @param	void
 * @return	void
*/
void	disable_ctrl_c_printing_chars(void)
{
	int rc;
	t_inf	info;

	rc = tcgetattr(0, &info.termios);
	if (rc != 0)
	{
		perror("tcgetattr");
		exit (1);
	}
	info.termios.c_lflag &= ~ECHOCTL;
	rc = tcsetattr(0, 0, &info.termios);
	if (rc != 0)
	{
		perror("tcsetattr");
		exit(1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_token	*token_list;
	t_scmd	*scmds_list;
	t_info	info;
	t_env	envi;
	t_inf	inf;
	char	*cmd_line;

	disable_ctrl_c_printing_chars();
	if (argc > 1 || ft_strncmp(argv[0], "./minishell", ft_strlen(argv[0])))
		return (printf("No smartass shenanigans, just the executable ;)\n"));
	token_list = NULL;
	scmds_list = NULL;
	cmd_line = NULL;
	info.env_cpy = copy_env(envp);
	init_struct(&envi, &inf);
	while (1)
	{
		ft_signals();
		cmd_line = readline("minishell-0.2$ ");
		if (!cmd_line)
			break ;
		if (cmd_line[0])
		{
			cmd_line[ft_strlen(cmd_line)] = '\0';
			shell_operation(cmd_line, token_list, scmds_list, info);
		}
	}
	free_info(info);
	return (0);
}
