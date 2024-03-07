/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:45:45 by vipalaci          #+#    #+#             */
/*   Updated: 2024/03/07 15:44:28 by amanjon-         ###   ########.fr       */
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
			// ft_print_lst_2(*envi);
			return ;
			// exit(1);
		}
		exit(127);
	}
	execve(scmd->cmd_path, scmd->cmd_args, info->env_cpy);
}

void	ft_builtin(t_env **envi, char **args, t_info *info)
{
	printf("args[0] = %s\n", args[0]);
	printf("args[1] = %s\n", args[1]);
	ft_builtins(args, envi, info->env_cpy);
	
/* The code snippet `printf("*****************************\n"); ft_print_lst_2(*envi);
printf("\n******************+\n\n");` is printing the contents of a linked list pointed to by the
`envi` pointer. */
	// printf("*****************************\n");
	// ft_print_lst_2(envi);
	// printf("\n******************+\n\n");
	// printf("%s\n", args[0]);	// Vini
}
