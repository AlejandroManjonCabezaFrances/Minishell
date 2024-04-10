/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:57:39 by amanjon-          #+#    #+#             */
/*   Updated: 2024/04/08 13:07:06 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_builtin(t_scmd *scmd, t_info *info)
{
	if (scmd->infile != -1)
		ft_dup(scmd->infile, STDIN_FILENO);
	if (scmd->outfile != -1)
		ft_dup(scmd->outfile, STDOUT_FILENO);
	ft_builtins(scmd->cmd_args, info);
	free_array(info->env_cpy);
	info->env_cpy = ft_convert_list_to_double_pointer(info->envi);
	return (1);
}
