/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:29:20 by amanjon-          #+#    #+#             */
/*   Updated: 2024/03/08 09:59:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int g_signal_code = 0;
int	exit_status = 0;

void	shell_operation(t_env **envi, char *line, t_token *list, t_scmd *scmds, t_info info)
{
	int	err;

	// ft_print_lst_2(*envi);
	err = lexer(&list, line);
	add_history(line);
	if (err != 1)
		panic(err, NULL, NULL);
	if (err == 1)
	{
		err = parser(&list, &scmds, &info);
		if (err != 1)
			panic(err, NULL, NULL);
		err = executer(envi, &scmds, &info);
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
void	init_struct(t_env **envi, t_inf *inf)
{
	
	inf->cwd = NULL;
	(*envi)->env_n = NULL;
	(*envi)->flag = 0;			// new fusion minishell
	(*envi)->pwd = NULL;		// new fusion minishell
	(*envi)->old_pwd = NULL;	// new fusion minishell
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

void	ft_print_double_pointer(char **double_pointer)
{
	int i;
	
	i = 0;
	while (double_pointer[i])
	{
		printf("double_pointer[%d] = %s\n", i, double_pointer[i]);
		i++;
	}
}

void	ft_update_env(t_env **envi, char **env_cpy)
{
	ft_print_double_pointer(env_cpy);
	ft_print_lst_2(*envi);
}

int	main(int argc, char **argv, char **envp)
{
	t_token	*token_list;
	t_scmd	*scmds_list;
	t_info	info;
	t_env	*envi;
	t_inf	inf;
	char	*cmd_line;

	token_list = NULL;
	scmds_list = NULL;
	cmd_line = NULL;
	envi = NULL;
	info.envi = NULL;	// iniciar *envi dentro de info que apunta a mi estructura. NO LA USO
	// ################ env -i ./minishell ######################
	if (*envp == NULL)
		ft_simulate_env_i_minishell(&envi);
	else
		ft_linked_list_env(&envi, envp);
	disable_ctrl_c_printing_chars();
	if (argc > 1 || ft_strncmp(argv[0], "./minishell", ft_strlen(argv[0])))
		return (printf("No smartass shenanigans, just the executable ;)\n"));
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
			shell_operation(&envi, cmd_line, token_list, scmds_list, info);
		}
		// printf("\n printenado en el main\n");
		// ft_print_lst_2(envi);
		// printf("\n *********************\n");
		// ft_update_env(&envi, info.env_cpy);
	}
	free_info(info);
	return (0);
}
