/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:45:45 by vipalaci          #+#    #+#             */
/*   Updated: 2024/03/21 10:45:38 by amanjon-         ###   ########.fr       */
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
			ft_builtin(scmd->cmd_args, info);
			exit(1);
		}
		else
			exit(127);
	}
	if (info->path != NULL)
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
			ft_builtin(scmd->cmd_args, info);
			return ;
			// exit(1);
		}
		exit(127);
	}
	if (info->path != NULL)
		execve(scmd->cmd_path, scmd->cmd_args, info->env_cpy);
}

void	ft_builtin(char **args, t_info *info)
{
	ft_builtins(args,info);
	
	// info->env_cpy = ft_convert_list_to_double_pointer(&info->envi);
	// printf("printeando mi lista envi pasada a doble puntero\n");
	// ft_print_double_pointer(info->env_cpy);
	
/* The code snippet `printf("*****************************\n"); ft_print_lst_2(*envi);
printf("\n******************+\n\n");` is printing the contents of a linked list pointed to by the
`envi` pointer. */
	// printf("*****************************\n");
	// ft_print_lst_2(envi);
	// printf("\n******************+\n\n");
	// printf("%s\n", args[0]);	// Vini
}
