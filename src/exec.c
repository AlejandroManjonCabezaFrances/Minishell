/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:16:05 by vipalaci          #+#    #+#             */
/*   Updated: 2024/04/19 13:03:13 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parent_close(int fd_1, int fd_2, t_scmd *scmd)
{
	close(fd_1);
	close(fd_2);
	free (scmd);
}

int	exec_cmds(t_scmd **scmds_list, t_info *info)
{
	t_scmd	*aux;
	int		pipe_fd[2];
	int		upstream;

	aux = *scmds_list;
	upstream = -1;
	while (aux)
	{
		if (pipe(pipe_fd) == -1)
			return (PIPE_ERR);
		if (!aux->next)
			last_command(aux, info, upstream);
		else
			exec_command(aux, info, upstream, pipe_fd);
		close(pipe_fd[1]);
		upstream = pipe_fd[0];
		aux = aux->next;
	}
	while (wait(NULL) != -1 || errno != ECHILD)
		;
	parent_close(pipe_fd[0], upstream, aux);
	return (1);
}

int	check_builtin(t_scmd *scmd)
{
	char	*str;

	str = scmd->cmd_name;
	if (str)
	{
		if (!ft_strncmp(str, "echo", ft_strlen(str)))
			return (0);
		else if (!ft_strncmp(str, "cd", ft_strlen(str)))
			return (0);
		else if (!ft_strncmp(str, "pwd", ft_strlen(str)))
			return (0);
		else if (!ft_strncmp(str, "export", ft_strlen(str)))
			return (0);
		else if (!ft_strncmp(str, "unset", ft_strlen(str)))
			return (0);
		else if (!ft_strncmp(str, "env", ft_strlen(str)))
			return (0);
		else if (!ft_strncmp(str, "exit", ft_strlen(str)))
			return (0);
		else
			return (1);
	}
	return (2);
}

void	check_cmds(t_scmd **scmds_list, t_info *info)
{
	t_scmd	*aux;
	int		err;

	aux = *scmds_list;
	while (aux)
	{
		err = check_builtin(aux);
		if (err == 1)
		{
			err = check_path(aux);
			if (err == 0)
				aux->cmd_path = ft_strdup(aux->cmd_name);
			else if (err == 1)
			{
				err = get_cmd(aux, info);
				if (err != 0)
					panic(COMMAND_ERR, NULL, NULL);
			}
			else
				panic(err, NULL, NULL);
		}
		aux = aux->next;
	}
	g_signal_code = err;
	free(aux);
}

int	executer(t_scmd **scmds_list, t_info *info)
{
	check_cmds(scmds_list, info);
	if (!(*scmds_list)->next & (check_builtin(*scmds_list) == 0))
		return (exec_builtin(*scmds_list, info));
	else
		return (exec_cmds(scmds_list, info));
}
