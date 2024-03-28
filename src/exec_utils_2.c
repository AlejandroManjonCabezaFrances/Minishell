/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:45:45 by vipalaci          #+#    #+#             */
/*   Updated: 2024/03/28 13:58:36 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	void	ft_upper_shlvl(t_env *envi)
{
	t_env	*aux;
	char	*n_shlvl;

	aux = envi;
	n_shlvl = NULL;
	while (aux)
	{
		if (ft_strncmp(aux->content, "SHLVL=", 6) == 0)
		{
			if (ft_atoi((ft_strrchr(aux->content, '=')) + 1) >= 1)
			{
				n_shlvl = ft_itoa((ft_atoi(aux->content + 6) + 1));
				ft_replace_node(envi, "SHLVL=", n_shlvl);
				free(n_shlvl);
				break ;
			}
		}
		aux = aux->next;
	}
}

static	void	ft_nested_minishell(t_info *info)
{
	ft_upper_shlvl(info->envi);
	info->env_cpy = ft_convert_list_to_double_pointer(&info->envi);
}

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
	{
		if (!ft_strncmp(scmd->cmd_args[0], "./minishell", 11))
			ft_nested_minishell(info);
		execve(scmd->cmd_path, scmd->cmd_args, info->env_cpy);
	}
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
			exit(1);
		}
		exit(127);
	}
	if (info->path != NULL)
	{
		if (!ft_strncmp(scmd->cmd_args[0], "./minishell", 11))
			ft_nested_minishell(info);
		execve(scmd->cmd_path, scmd->cmd_args, info->env_cpy);
	}
}

void	ft_builtin(char **args, t_info *info)
{
	ft_builtins(args, info);
	info->env_cpy = ft_convert_list_to_double_pointer(&info->envi);
}
