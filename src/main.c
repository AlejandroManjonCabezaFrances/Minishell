/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:29:20 by amanjon-          #+#    #+#             */
/*   Updated: 2024/01/03 15:45:56 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * This function disable chars printed by ctrl+c '^C'
 * @param	void
 * @return	void
*/
// static void	ft_disable_ctrl_c_printing_chars(t_inf inf)
// {
// 	int rc;

// 	rc = tcgetattr(0, &inf.termios);
// 	if (rc != 0)
// 	{
// 		perror("tcgetattr");
// 		exit (1);
// 	}
// 	inf.termios.c_lflag &= ~ECHOCTL;
// 	rc = tcsetattr(0, 0, &inf.termios);
// 	if (rc != 0)
// 	{
// 		perror("tcsetattr");
// 		exit(1);
// 	}
// }

char	**copy_env(char **envp)
{
	char	**env_cpy;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	env_cpy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env_cpy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env_cpy[i] = ft_strdup(envp[i]);
		i++;
	}
	env_cpy[i] = NULL;
	return (env_cpy);
}

int	main(int argc, char **argv, char **env)
{
	// t_inf	inf;
	// t_scmd	*scmds_list;
	t_token	*token_list;
	char	*cmd_line;
	char	**env_cpy;
	int		err;
	
	(void) argv;
	(void) env;
	// inf.env = NULL;
	// inf.pwd = NULL;
	token_list = NULL;
	cmd_line = NULL;
	env_cpy = copy_env(env);
	// ft_disable_ctrl_c_printing_chars(inf);
	if (argc != 1)
	{
		printf("enter only the executable ./minishell, thanks\n");
		return (1);
	}
	/* ft_copy_env(&g_info, env); */
	// ft_get_env(&g_info, env);
	while (1)
	{
		ft_signals();
		cmd_line = readline("minishell-0.2$ ");
		if (!cmd_line)
			panic(READLINE_ERR, NULL, NULL);
		cmd_line[ft_strlen(cmd_line)] = '\0';
		err = lexer(&token_list, cmd_line, env_cpy);
		if (err != 1)
			panic (err, NULL, NULL);
		add_history(cmd_line);
		// parse(token_list, &scmds_list);
		// tcsetattr(0, 0, &inf.termios);
		ms_print_lst(token_list);
		free(cmd_line);
		ms_lstclear(&token_list);
	}
	return (0);
}
