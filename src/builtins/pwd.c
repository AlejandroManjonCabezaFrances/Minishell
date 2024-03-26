/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:26:05 by marvin            #+#    #+#             */
/*   Updated: 2024/01/17 14:26:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Replicate the pwd command
 * @param	char **cmd
 * @return	void
*/
void	ft_pwd(char **cmd)
{
	char	cwd[PATH_MAX];

	if (cmd[1] != NULL)
	{
		ft_putstr_fd("pwd without arguments according to subject\n", 2);
		return ;
	}
	else
	{
		getcwd(cwd, sizeof(cwd));
		printf("%s\n", cwd);
	}
	return ;
}
