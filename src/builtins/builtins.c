/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:41:16 by amanjon-          #+#    #+#             */
/*   Updated: 2024/04/10 11:58:36 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * We compare that we have found a "builtin" command in the prompt
 * @param	char **cmd, t_info *info
 * @return	void
*/
void	ft_builtins(char **cmd, t_info *info)
{
	if (ft_strcmp(*cmd, "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(*cmd, "env") == 0)
		ft_env(&(info->envi), cmd);
	else if (ft_strcmp(*cmd, "export") == 0)
		ft_export(cmd, &(info->envi));
	else if (ft_strcmp(*cmd, "pwd") == 0)
		ft_pwd(cmd);
	else if (ft_strcmp(*cmd, "unset") == 0)
		ft_unset(cmd, &(info->envi));
	else if (ft_strcmp(*cmd, "cd") == 0)
		ft_cd(cmd, info->envi, info->env_cpy);
	else if (ft_strcmp(*cmd, "exit") == 0)
		ft_exit(cmd, info);
}
