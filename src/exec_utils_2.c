/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:45:45 by vipalaci          #+#    #+#             */
/*   Updated: 2024/03/05 15:10:49 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_child(t_scmd *scmd, t_info *info, int upstream, int *pipe_fd)
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
			ft_builtin(scmd->cmd_args);
			exit(1);
		}
		else
			exit(127);
	}
	execve(scmd->cmd_path, scmd->cmd_args, info->env_cpy);
}

void	last_child(t_scmd *scmd, t_info *info, int upstream)
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
			ft_builtin(scmd->cmd_args);
			exit(1);
		}
		exit(127);
	}
	execve(scmd->cmd_path, scmd->cmd_args, info->env_cpy);
}

void	ft_builtin(char **args)
{
	printf("%s\n", args[0]);
}
