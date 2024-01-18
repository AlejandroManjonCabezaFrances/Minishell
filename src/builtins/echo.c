/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:13:09 by amanjon-          #+#    #+#             */
/*   Updated: 2024/01/18 17:40:53 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// gcc -Wall -Werror -Wextra ../../libft/Libft/src/ft_putstr_fd.c ../utils.c builtins.c pwd.c echo.c -o echo && ./echo

static int	ft_flag_n(char *str)
{	
	// if (str[0] == '-')
	// 	(*len)++;
	// if (str[0] != '-' && str[1] != 'n')
	// 	return (1);
	int i;

	i = 1;
	while (str[i] == 'n')
		i++;
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
	while (cmd[len] && cmd[len][0] == '-')
	{
		if (ft_flag_n(cmd[len]) == 1)
			flag = 1;
		len++;
	}
	while (cmd[len])
	{
		ft_putstr_fd(cmd[len], 1);
		if (cmd[len + 1])
			write(1, " ", 1);
		len++;
	}
	// printf("\nflag = %i\n", flag);
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
	
	// char *cmd[7];		// con flag -n
	// cmd[0] = "echo";
	// cmd[1] = "-nnnn";
	// cmd[2] = "-nnnn";
	// cmd[3] = "-nnnn";
	// cmd[4] = "lo        que diga el papi";
	// cmd[5] = "alex que tal";
	// cmd[6] = NULL;

	ft_builtins(cmd);
    return (0);
}