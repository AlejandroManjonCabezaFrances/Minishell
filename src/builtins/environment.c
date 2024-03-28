/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:13:38 by amanjon-          #+#    #+#             */
/*   Updated: 2024/03/28 08:34:12 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * We print the nodes that contain a '='
 * @param	t_env *temp
 * @return	static	void
*/
static	void	ft_print_lst_3(t_env *temp)
{
	while (temp)
	{
		if (ft_strchr(temp->content, '=') != 0)
			printf("%s\n", temp->content);
		temp = temp->next;
	}
}

/**
 * Replicate the env command printing the environment list
 * @param	t_env *envi
 * @return	void
*/
void	ft_env(t_env **envi, char **cmd)
{
	if (cmd[1] != NULL)
	{
		printf("env: %s: No such file or directory\n", cmd[1]);
		g_signal_code = 127;
	}
	else
		ft_print_lst_3(*envi);
}
