/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:20:52 by amanjon-          #+#    #+#             */
/*   Updated: 2024/01/17 13:25:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(fd, &str[i], 1);
		i++;
	}
}

int	ft_isspace(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}



// static void	ft_echo_writing(char **list, int idx)
// {
// 	while (list[idx])
// 	{
// 		ft_putstr_fd(list[idx++], 1);
// 	}
// }

// static int	check_for_flag(char *str)
// {
// 	int	loc;

// 	loc = 1;
// 	if (str[0] != '-')
// 		return (0);
// 	while (str[loc] == 'n')
// 		loc++;
// 	if (ft_isspace(str[loc]) || !str[loc])
// 		return (1);
// 	return (0);
// }

// /**
//  * * This should recreate the bash funtion "echo".
//  * @param list	vector of arguments containing records to echoed
// */
// void	ft_echo(char **argv)
// {
// 	int		n_flag;
// 	int		idx;

// 	n_flag = 0;
// 	idx = 1;
// 	if (argv[idx] == NULL)
// 	{
// 		write(1, "\n", 1);
// 		return ;
// 	}
// 	while (1)
// 	{
// 		if (!check_for_flag(argv[idx]))
// 			break ;
// 		idx++;
// 		n_flag = 1;
// 		if (!argv[idx])
// 			break ;
// 	}
// 	ft_echo_writing(argv, idx);
// 	if (!n_flag)
// 		write(1, "\n", 1);
// }




// static void	ft_echo_writing(char **cmd, int len)
// {
// 	while (cmd[len])
// 	{
// 		ft_epur_str(cmd[len]);
// 		len++;
// 	}
// }

void ft_epur_str(char *str)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while(str[k] != '\0')
		k++;
	k--;
	while(str[k] == ' ' || str[k] == '\t')
		k--;
	while(str[j] == ' ' || str[j] == '\t')
		j++;
	while(/* str[i] != '\0' &&  */i <=k)
	{
		while(str[i] == ' ' || str[i] == '\t')
			i++;
		if(str[i - 1] == ' ' && i > j)
			write(1, " ", 1);
		write(1, &str[i], 1);
		i++;
	}
	// write(1, "\n", 1);
}

static int	ft_flag_n(char *str/* , int len */)
{
	char *ptr;
	
	ptr = str;
	if (ptr[0] != '-')
		return (0);
	while (*ptr == 'n')
		ptr++;
	str = ptr;
	return (1);
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
	if (ft_flag_n(cmd[len]/* , len */) == 1)
		flag = 1;
	while (cmd[len])
	{
		ft_epur_str(cmd[len]);
		len++;
	}
	if (flag == 1)
		write(1, "\n", 1);
	// ft_echo_writing(cmd, len);
	
}

void	ft_builtins(char **cmd)
{
	if (ft_strcmp(*cmd, "echo") == 0)
		ft_echo(cmd);
	// else if (ft_strcmp(*cmd, "cd") == 0)
	// 	ft_cd(cmd);
	// else if (ft_strcmp(*cmd, "pwd") == 0)
	// 	ft_pwd(cmd);
	// else if (ft_strcmp(*cmd, "unset") == 0)
	// 	ft_unset(cmd);
	// else if (ft_strcmp(*cmd, "export") == 0)
	// 	ft_export(cmd);
	// else if (ft_strcmp(*cmd, "exit") == 0)
	// 	ft_exit(cmd);
}

int main() 
{
    char *cmd[] = {"echo","-n", "   hola          chicos", NULL};
    char **cmdPtr = cmd;
	
    ft_builtins(cmdPtr);

	// char *cmd[3];

	// cmd[0] = "echo";
	// cmd[1] = "lo que diga el papi";
	// cmd[2] = NULL;

	// ft_builtins(cmd);
    return (0);
}
// gcc -Wall -Werror -Wextra utils.c sandbox.c -o sandbox && ./sandbox
