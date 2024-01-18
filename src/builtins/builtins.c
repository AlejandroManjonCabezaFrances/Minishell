/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:41:16 by amanjon-          #+#    #+#             */
/*   Updated: 2024/01/18 11:39:40 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_builtins(char **cmd)
{
	if (ft_strcmp(*cmd, "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(*cmd, "pwd") == 0)
		ft_pwd(cmd);
	// else if (ft_strcmp(*cmd, "cd") == 0)
	// 	ft_cd(cmd);
	// else if (ft_strcmp(*cmd, "unset") == 0)
	// 	ft_unset(cmd);
	// else if (ft_strcmp(*cmd, "export") == 0)
	// 	ft_export(cmd);
	// else if (ft_strcmp(*cmd, "exit") == 0)
	// 	ft_exit(cmd);
    // else if (ft_strcmp(*cmd, "env") == 0)
	// 	ft_env(cmd);
}