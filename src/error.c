/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:45:54 by vipalaci          #+#    #+#             */
/*   Updated: 2024/04/15 12:49:50 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_array(char **str)
{
	int	i;

	i = 0;
	if (!str[i])
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str[i]);
	free(str);
	return ;
}

void	panic(int err, t_token **list, t_token *token)
{
	if (err == QUOTING_ERR)
		printf("no closing quotes found\n");
	else if (err == READLINE_ERR)
		printf("readline error\n");
	else if (err == PARSE_ERR)
		printf("parsing error\n");
	else if (err == INFILE_ERR)
		printf("no such file or directory\n");
	else if (err == OUTFILE_ERR)
		printf("error writing/creating file\n");
	else if (err == MALLOC_ERR)
		printf("malloc error\n");
	else if (err == COMMAND_ERR)
		printf("command not found\n");
	else if (err == PIPE_ERR)
		printf("pipe error\n");
	else if (err == FORK_ERR)
		printf("error during fork() call\n");
	if (list)
		ms_lstclear(list);
	if (token)
		free(token);
}
