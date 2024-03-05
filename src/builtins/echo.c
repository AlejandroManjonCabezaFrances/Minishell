/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:13:09 by amanjon-          #+#    #+#             */
/*   Updated: 2024/03/05 15:28:15 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// gcc -Wall -Werror -Wextra ../../libft/Libft/src/ft_putstr_fd.c ../utils.c unset.c ../sandbox2.c ../../libft/Libft/src/ft_strtrim.c ../../libft/Libft/src/ft_strjoin.c builtins.c cd.c exit.c env.c echo.c pwd.c export.c -o echo && ./echo

// ################ env -i ./minishell ######################
// gcc -Wall -Werror -Wextra ../../libft/Libft/src/ft_putstr_fd.c ../utils.c unset.c ../sandbox2.c ../../libft/Libft/src/ft_strtrim.c ../../libft/Libft/src/ft_strjoin.c builtins.c cd.c exit.c env.c echo.c pwd.c export.c -o echo && env -i ./echo
// ################ env -i ./minishell ######################

/**
 * Print the string that the function receives
 * @param	char **cmd, int len
 * @return	static void
*/
static	void	ft_writing_echo(char **cmd, int len)
{
	while (cmd[len])
	{
		ft_putstr_fd(cmd[len], STDOUT_FILENO);
		if (cmd[len + 1])
			write(1, " ", 1);
		len++;
	}
}

/**
 * Manage multiple flags -n
 * @param	char *str
 * @return	static int. TRUE or FALSE
*/
static	int	ft_flag_n(char *str)
{	
	int i;

	i = 1;
	while (str[i] == 'n')
		i++;
	if (str[i] != 'n' && str[i])
		return (FALSE);
	return (TRUE);
}

/**
 * Replicates the "echo" builtin, checking if it has flag -n
 * @param	char **cmd
 * @return	void
*/
void	ft_echo(char **cmd)
{
	int len;
	int flag;

	len = 1;
	flag = 0;
	while (cmd[len] && cmd[len][0] == '-')
	{
		if (ft_flag_n(cmd[len]) == TRUE)
		{
			flag = TRUE;
			len++;
		}
		else
			break ;
	}
	ft_writing_echo(cmd, len);
	if (flag == FALSE)
		write(1, "\n", 1);
}

// int main(int argc, char **argv, char **env) 
// {
// 	t_env	*envi;
// 	(void) 	argc;
// 	(void) 	argv;
	
// 	envi = NULL;
// 	ft_linked_list_env(&envi, env);

// /* 	char *cmd[3];
// 	cmd[0] = "echo";
// 	cmd[1] = NULL; */
	
// 	char *cmd[3];			// sin flag -n
// 	cmd[0] = "echo";
// 	cmd[1] = "lo        que diga el papi";
// 	cmd[2] = NULL;
	
// /* 	char *cmd[7];			// con flag -n
// 	cmd[0] = "echo";
// 	cmd[1] = "-nnn";
// 	cmd[2] = "-nnnn";
// 	cmd[3] = "-nnnn";
// 	cmd[4] = "lo        que diga el papi";
// 	cmd[5] = "alex que tal";
// 	cmd[6] = NULL; */

// 	ft_builtins(cmd, &envi, env);
	
//     return (0);
// } 

// g_signal_code = 0; builtin echo, en bash siempre el   echo $? = 0