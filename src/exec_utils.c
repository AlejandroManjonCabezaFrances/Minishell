/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:10:11 by vipalaci          #+#    #+#             */
/*   Updated: 2024/03/05 14:14:35 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_dup(int old_fd, int new_fd)
{
	dup2(old_fd, new_fd);
	close(old_fd);
}

int	exec_command(t_scmd *scmd, t_info *info, int upstream, int *pipe_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (FORK_ERR);
	if (pid == 0)
		exec_child(scmd, info, upstream, pipe_fd);
	close(upstream);
	return (1);
}

int	last_command(t_scmd *scmd, t_info *info, int upstream)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (FORK_ERR);
	if (pid == 0)
		last_child(scmd, info, upstream);
	close(upstream);
	return (1);
}

int	get_cmd(t_scmd *scmd, t_info *info)
{
	char	*aux;
	char	*command;
	int		i;

	i = 0;
	while (info->bin_paths[i])
	{
		aux = ft_strjoin(info->bin_paths[i], "/");
		command = ft_strjoin(aux, scmd->cmd_name);
		free(aux);
		if (access(command, F_OK & R_OK & X_OK) == 0)
		{
			scmd->cmd_path = command;
			return (1);
		}
		free(command);
		i++;
	}
	return (COMMAND_ERR);
}

int	check_path(t_scmd *scmd)
{
	if (scmd->cmd_name[0] == '.' || scmd->cmd_name[0] == '/')
	{
		if (access(scmd->cmd_name, F_OK & R_OK & X_OK) == 0)
			return (1);
		else
			return (COMMAND_ERR);
	}
	return (0);
}
