/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:41:16 by amanjon-          #+#    #+#             */
/*   Updated: 2024/03/12 15:13:03 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_builtins(char **cmd, t_info *info)
{
	(void) envi;
	printf("entra ft_builtins\n");
	printf("*cmd = %s\n", *cmd);
	if (ft_strcmp(*cmd, "echo") == 0)
	{
		printf("ENTRA EN MI ECHO?\n\n");
		ft_echo(cmd);
	}
    else if (ft_strcmp(*cmd, "env") == 0)
	{
		printf("ENTRA EN MI ENV?\n\n");
		ft_env(envi, cmd);
	}
	else if (ft_strcmp(*cmd, "export") == 0)
	{
		printf("ENTRA EN MI EXPORT?\n\n");
		ft_export(cmd, info->envi, info->declare);
	}
	else if (ft_strcmp(*cmd, "pwd") == 0)
		ft_pwd(cmd);
	else if (ft_strcmp(*cmd, "unset") == 0)
	{
		printf("ENTRA EN MI UNSET?\n\n");
		ft_unset(cmd, envi);
	}
	else if (ft_strcmp(*cmd, "cd") == 0)
		ft_cd(cmd, *envi, env);
	else if (ft_strcmp(*cmd, "exit") == 0)
		ft_exit(cmd, *envi);
	// ft_print_lst_2(*envi);
} 