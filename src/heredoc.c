/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vini <vini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:16:38 by amanjon-          #+#    #+#             */
/*   Updated: 2024/04/11 18:04:49 by vini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_heredoc_line(char *line, char *content)
{
	if (!line || !ft_strncmp(line, content, ft_strlen(content)))
		return (0);
	return (1);
}

int	open_heredoc(t_scmd *scmd, t_token *token)
{
	char	*line;
	int		file;

	file = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file < 0)
		return (INFILE_ERR);
	while (1)
	{
		ft_signal_interrupt();
		write(1, "> ", 2);
		line = get_next_line(0);
		ft_signals_noninteractive();
		if (!check_heredoc_line(line, token->content))
			break ;
		write(file, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(file);
	scmd->infile = open(".heredoc", O_RDONLY, 0644);
	if (scmd->infile < 0)
		return (INFILE_ERR);
	scmd->heredoc = 1;
	return (1);
}

// static void	read_loop(int infile, char *line, char *eof)
// {
// 	while (line)
// 	{
// 		line[ft_strlen(line)] = '\0';
// 		if ((ft_strncmp(line, eof, ft_strlen(eof)) == 0)
// 			&& (ft_strlen(line) == ft_strlen(eof)))
// 			break ;
// 		ft_putstr_fd(line, infile);
// 		ft_putstr_fd("\n", infile);
// 		free(line);
// 		line = readline("> ");
// 	}
// 	free(line);
// }

// int	open_heredoc(t_scmd *scmd, t_token *token)
// {
// 	pid_t	pid;
// 	char	*line;

// 	if (scmd->infile != -1)
// 		close(scmd->infile);
// 	scmd->infile = open(token->content, O_APPEND | O_CREAT | O_RDWR, 0644);
// 	if (scmd->infile < 0)
// 		return (INFILE_ERR);
// 	signal(SIGINT, SIG_IGN);
// 	signal(SIGQUIT, SIG_IGN);
// 	pid = fork();
// 	if (pid == -1)
// 		return (FORK_ERR);
// 	if (pid == 0)
// 	{
// 		signal(SIGINT, SIG_DFL);
// 		signal(SIGQUIT, SIG_IGN);
// 		line = readline("> ");
// 		read_loop(scmd->infile, line, token->content);
// 		close(scmd->infile);
// 		exit(1);
// 	}
// 	else
// 		wait(NULL);
// 	return (1);
// }
