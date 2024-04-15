/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:59:44 by vipalaci          #+#    #+#             */
/*   Updated: 2024/04/15 12:54:41 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_only_space(char *str)
{
	int	i;
	int	k;

	i = -1;
	k = 0;
	while (str[++i])
		if (!is_space(str[i]))
			k++;
	return (k);
}

void	shell_operation(char *line, t_token *list, t_scmd *scmds, t_info *info)
{
	int	err;

	err = lexer(&list, line);
	add_history(line);
	if (err != 1)
		panic(err, NULL, NULL);
	else
	{
		err = parser(&list, &scmds, info);
		if (err != 1)
			panic(err, NULL, NULL);
		else if (err == 1)
			err = executer(&scmds, info);
	}
	if (err != 1)
		g_signal_code = 1;
	if (info->bin_paths)
		free_array(info->bin_paths);
	// free(line);
	if (list)
		free_list(list);
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
		if (!ft_only_space(cmd_line))
		{
			free(cmd_line);
			return (0);
		}
		shell_operation(cmd_line, token_list, scmds_list, info);
	}
	free(cmd_line);
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
