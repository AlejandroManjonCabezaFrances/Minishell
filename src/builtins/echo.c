/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:13:09 by amanjon-          #+#    #+#             */
/*   Updated: 2024/03/25 14:35:43 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
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
	int	i;

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
	int	len;
	int	flag;

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
