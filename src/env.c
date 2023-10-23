/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:23:02 by amanjon-          #+#    #+#             */
/*   Updated: 2023/10/23 15:43:01 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_get_env(t_inf *info, char **env)
{
	char *shlvl;
	int	i;

	shlvl = NULL;
	i = 0;
	if (env[i] == NULL)
		return ;
	while (env[i])
	{
		printf("env = %s\n", env[i]);
		i++;
	}
	info->env = (char **)malloc(sizeof(char *) * (i));
	if (info->env == NULL)
		return;
	i = 0;
	while (env[i])
	{
		if (ft_strcmp("SHLVL=", env[i], 6) == 0)
		{
			
		}
		i++;
	}
}
