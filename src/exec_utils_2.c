/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:45:45 by vipalaci          #+#    #+#             */
/*   Updated: 2024/03/07 13:52:34 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_child(t_env **envi, t_scmd *scmd, t_info *info, int upstream, int *pipe_fd)
{
	close(pipe_fd[0]);
	if (scmd->infile != -1)
		ft_dup(scmd->infile, STDIN_FILENO);
	else if (upstream != -1)
		ft_dup(upstream, STDIN_FILENO);
	if (scmd->outfile != -1)
		ft_dup(scmd->outfile, STDOUT_FILENO);
	else if (pipe_fd[1] != -1)
		ft_dup(pipe_fd[1], STDOUT_FILENO);
	if (!scmd->cmd_path)
	{
		if (check_builtin(scmd) == 1)
		{
			ft_builtin(envi, scmd->cmd_args, info);
			exit(1);
		}
		else
			exit(127);
	}
	execve(scmd->cmd_path, scmd->cmd_args, info->env_cpy);
}

void	last_child(t_env **envi, t_scmd *scmd, t_info *info, int upstream)
{
	if (scmd->infile != -1)
		ft_dup(scmd->infile, STDIN_FILENO);
	else if (upstream != -1)
		ft_dup(upstream, STDIN_FILENO);
	if (scmd->outfile != -1)
		ft_dup(scmd->outfile, STDOUT_FILENO);
	if (!scmd->cmd_path)
	{
		if (check_builtin(scmd) == 1)
		{
			ft_builtin(envi, scmd->cmd_args, info);
			exit(1);
		}
		exit(127);
	}
	execve(scmd->cmd_path, scmd->cmd_args, info->env_cpy);
}

void	ft_builtin(t_env **envi, char **args, t_info *info)
{
	printf("antes de printear la lista ******************\n");
	// ft_print_lst_2(info->envi);
	printf("entra aqui?\n");
	ft_builtins(args, envi, info->env_cpy);
	// printf("%s\n", args[0]);	// Vini
}
