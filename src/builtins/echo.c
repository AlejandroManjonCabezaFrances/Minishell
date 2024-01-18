/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:13:09 by amanjon-          #+#    #+#             */
/*   Updated: 2024/01/18 13:13:18 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// gcc -Wall -Werror -Wextra ../../libft/Libft/src/ft_putstr_fd.c ../utils.c builtins.c pwd.c echo.c -o echo && ./echo

// static void    ft_epur_str(char *str)
// {
// 	int i;
// 	int j;
// 	int k;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	while(str[k] != '\0')
// 		k++;
// 	k--;
// 	while(str[k] == ' ' || str[k] == '\t')
// 		k--;
// 	while(str[j] == ' ' || str[j] == '\t')
// 		j++;
// 	while(str[i] != '\0' && i <=k)
// 	{
// 		while(str[i] == ' ' || str[i] == '\t')
// 			i++;
// 		if(str[i - 1] == ' ' && i > j)
// 			write(1, " ", 1);
// 		write(1, &str[i], 1);
// 		i++;
// 	}
// }

static void	ft_writing_echo(char **cmd, int len)
{
	printf("cmd[1] = %s\n", cmd[1]);
	while (cmd[len])
	{
		ft_putstr_fd(cmd[len], 1);
		// if (cmd[len])
		// write(1, " ", 1);
		len++;
	}
}	

static int	ft_flag_n(char *str, int *len)
{	
	if (str[0] != '-')
		return (1);
	while (str[*len] == 'n')
		(*len)++;
	return (0);
}

void	ft_echo(char **cmd)
{
	int len;
	int flag;

	len = 1;
	flag = 0;
	if (cmd[len] == NULL)
	{
		write(1,"\n", 1);
		return ;		
	}
	if (ft_flag_n(cmd[len], &len) == TRUE)
		flag = 1;
	// while (cmd[len])
	// {
		// ft_epur_str(cmd[len]);
		ft_writing_echo(cmd, len);
	// 	printf("\nlen = %d\n", len);
	// 	len++;
	// }
	if (flag == TRUE)
		write(1, "\n", 1);
}

int main() 
{
    // char *cmd[] = {"echo",/* "-n", */ "hola diana" "alex que tal", NULL};
    // char **cmdPtr = cmd;
	
    // ft_builtins(cmdPtr);

	char *cmd[4];

	cmd[0] = "echo";
	cmd[1] = "lo que diga el papi";
	cmd[2] = "alex que tal";
	cmd[3] = NULL;

	ft_builtins(cmd);
    return (0);
}