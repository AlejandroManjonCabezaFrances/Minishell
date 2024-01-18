/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:13:09 by amanjon-          #+#    #+#             */
/*   Updated: 2024/01/18 16:28:07 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// gcc -Wall -Werror -Wextra ../../libft/Libft/src/ft_putstr_fd.c ../utils.c builtins.c pwd.c echo.c -o echo && ./echo

static int	ft_flag_n(char *str, int *len)
{	
	if (str[0] == '-')
		(*len)++;
	if (str[0] != '-' && str[1] != 'n')
		return (1);
	return (0);
}

void	ft_echo(char **cmd)
{
	int len;
	int flag;

	len = 1;
	flag = 0;
	if (cmd[len] == NULL)
		return ;		
	if (ft_flag_n(cmd[len], &len) == TRUE)
		flag = 1;
	while (cmd[len])
	{
		ft_putstr_fd(cmd[len], 1);
		if (cmd[len + 1])
			write(1, " ", 1);
		len++;
	}
	if (flag == TRUE)
		write(1, "\n", 1);
}

int main() 
{
	char *cmd[4];			// sin flag -n
	cmd[0] = "echo";
	cmd[1] = "lo        que diga el papi";
	cmd[2] = "alex que tal";
	cmd[3] = NULL;
	
	// char *cmd[5];		// con flag -n
	// cmd[0] = "echo";
	// cmd[1] = "-nnnn";
	// cmd[2] = "lo        que diga el papi";
	// cmd[3] = "alex que tal";
	// cmd[4] = NULL;

	ft_builtins(cmd);
    return (0);
}