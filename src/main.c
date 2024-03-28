/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:29:20 by amanjon-          #+#    #+#             */
/*   Updated: 2024/03/28 08:30:38 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_signal_code = 0;

void	shell_operation(char *line, t_token *list, t_scmd *scmds, t_info *info)
{
	int	err;

	err = lexer(&list, line);
	add_history(line);
	if (err != 1)
		panic(err, NULL, NULL);
	if (err == 1)
	{
		err = parser(&list, &scmds, info);
		if (err != 1)
			panic(err, NULL, NULL);
		err = executer(&scmds, info);
		if (err != 1)
			panic(err, NULL, NULL);
	}
	free(line);
	ms_lstclear(&list);
	ms_close_fds(&scmds);
	ms_cmdclear(&scmds);
}

/**
 * This function disable chars printed by ctrl+c '^C'
 * @param	void
 * @return	void
*/
void	disable_ctrl_c_printing_chars(void)
{
	int		rc;
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

/**
 * Loop content, signals, readline and main function of the program
 * @param	t_info *info, t_token *token_list, t_scmd *scmds_list, char *cmd_line
 * @return	int
*/
int	loop(t_info *info, t_token *token_list, t_scmd *scmds_list, char *cmd_line)
{
	ft_signals();
	cmd_line = readline("minishell-0.2$ ");
	if (!cmd_line)
		return (1);
	if (cmd_line[0])
	{
		cmd_line[ft_strlen(cmd_line)] = '\0';
		shell_operation(cmd_line, token_list, scmds_list, info);
	}
	return (0);
}

/**
 * We copy the env received from the int main and if it is null, we create an env
 * @param	t_info *info, int argc, char **argv, char **envp
 * @return	int
*/
int	ft_handle_env_execut(t_info *info, int argc, char **argv, char **envp)
{
	if (*envp == NULL)
		ft_simulate_env_i_minishell(&(info->envi), info);
	else
	{
		ft_linked_list_env(&(info->envi), envp);
		info->env_cpy = copy_env(envp);
	}
	disable_ctrl_c_printing_chars();
	if (argc > 1 || ft_strncmp(argv[0], "./minishell", ft_strlen(argv[0])))
		return (printf("No smartass shenanigans, just the executable ;)\n"));
	return (0);
}

 void leaks(void)
{
   system("leaks -q minishell");
}

int	main(int argc, char **argv, char **envp)
{
	t_token	*token_list;
	t_scmd	*scmds_list;
	t_info	info;
	char	*line;

	info.envi = NULL;
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
	}
	free(line);
	ms_lstclear(&token_list);
	free_array(info.env_cpy);
	free_array(info.bin_paths);
	ft_lstclear_ms(&(info.envi), &del_ms);
	atexit(leaks);
	return (0);
}
// info.flag_exit --> para cerrar minishell en caso de SHLVL=1,
// se ejecuta el break en proceso builtin pero no salimos por proceso padre