/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:29:20 by amanjon-          #+#    #+#             */
/*   Updated: 2024/02/16 09:19:47 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int g_signal_code = 0;

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
void	init_struct(t_inf *inf)
{
	inf->env = NULL;
	inf->pwd = NULL;
}
/**
 * This function disable chars printed by ctrl+c '^C'
 * @param	void
 * @return	void
*/
void	disable_ctrl_c_printing_chars(t_inf inf)
{
	int rc;

	rc = tcgetattr(0, &inf.termios);
	if (rc != 0)
	{
		perror("tcgetattr");
		exit (1);
	}
	inf.termios.c_lflag &= ~ECHOCTL;
	rc = tcsetattr(0, 0, &inf.termios);
	if (rc != 0)
	{
		perror("tcsetattr");
		exit(1);
	}
}

char	**copy_env(char **env)
{
	char	**env_cpy;
	int		i;

	i = 0;
	while (env[i])
		i++;
	env_cpy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env_cpy)
		return (NULL);
	i = 0;
	while (env[i])
	{
		env_cpy[i] = ft_strdup(env[i]);
		i++;
	}
	env_cpy[i] = NULL;
	return (env_cpy);
}

int	main(int argc, char **argv, char **env)
{
	t_inf	inf;
	t_token	*token_list;
	// t_scmd	*scmds_list;
	char	*cmd_line;
	char	**env_cpy;
	int		err;
	(void) argv;
	
	token_list = NULL;
	cmd_line = NULL;
	env_cpy = copy_env(env);
	init_struct(&inf);
	disable_ctrl_c_printing_chars(inf);
	check_argc(argc);
	// ft_copy_env(&g_info, env);
	while (1)
	{
		ft_signals();
		cmd_line = readline("minishell-0.2$ ");
		ft_set_signals_noninteractive();
		if (!cmd_line)
			panic(READLINE_ERR, NULL, NULL);
		// cmd_line[ft_strlen(cmd_line)] = '\0';
		err = lexer(&token_list, cmd_line, env_cpy);
		if (err != 1)
			panic (err, NULL, NULL);
		add_history(cmd_line);
		// parse(token_list, &scmds_list);
		print_lst_ms(token_list);
		// tcsetattr(0, 0, &inf.termios);
		free(cmd_line);
		lstclear_ms(&token_list);
	}
	return (0);
}
