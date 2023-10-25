/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:23:02 by amanjon-          #+#    #+#             */
/*   Updated: 2023/10/25 11:37:25 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// ################ Como hacer que el env sea null? ######################
void	ft_when_env_is_null(t_inf *info)
{
	info->env = malloc(sizeof(char *) * (3));
	info->env[0] = ft_strjoin("PWD=", getcwd(info->pwd, sizeof(info->pwd)));
	info->env[1] = ft_strdup("SHLVL=1");
	info->env[2] = ft_strdup("_=/usr/bin/env");
	printf("info->env[0] = %s\n", info->env[0]);
	printf("info->env[1] = %s\n", info->env[1]);
	printf("info->env[2] = %s\n", info->env[2]);
}

void	ft_get_env(t_inf *info, char **env)
{
	int		i;
	int j;
	char 	*temp;

	temp = NULL;
	i = 0;
	if (env[i] == NULL)
	{
		ft_when_env_is_null(info);
		return ;
	}
	while (env[i])
	{
		printf("env = %s\n", env[i]);
		i++;
	}
	info->env = (char **)malloc(sizeof(char *) * (i));
	if (info->env == NULL)
		return;
	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_strncmp("SHLVL=", env[i], 6) == 0)
		{
			if (ft_atoi(env[i] + 6) > 0)
			{
				temp = ft_itoa(ft_atoi((env[i]) + 6) + 1);
				info->env[j] = ft_strjoin("SHLVL=", temp);
				j++;
			}
			// else
		}
		if (ft_strncmp("OLDPWD=", env[i], 7) == 0)
		{
				info->env[j] = ft_strdup(env[i]);
				j++;
		}
		i++;
	}
	i = 0;
}

// void	store_env_aux(t_inf *info, char **env)
// {
// 	int		i;
// 	int		j;
// 	char	*tmp;

// 	i = -1;
// 	j = 0;
// 	while (env[++i])
// 	{
// 		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
// 		{
// 			if (ft_atoi(env[i] + 6) < 0)
// 				info->env[j++] = ft_strdup("SHLVL=0");
// 			else
// 			{
// 				tmp = ft_itoa(ft_atoi(env[i] + 6) + 1);
// 				info->env[j++] = ft_strjoin("SHLVL=", tmp);
// 				if (tmp != NULL)
// 					free(tmp);
// 			}
// 		}
// 		else if (ft_strncmp(env[i], "OLDPWD=", 7))
// 			info->env[j++] = ft_strdup(env[i]);
// 	}
// 	info->env[j] = NULL;
// }

// void	ft_get_env(t_inf *info, char **env)
// {
// 	int		i;

// 	i = 0;
// 	if (env[0] == NULL)
// 	{
// 		ft_when_env_is_null(info);
// 		return ;
// 	}
// 	while (env[i])
// 	{
// 		printf("env = %s\n", env[i]);
// 		i++;
// 	}
// 	info->env = (char **)malloc(sizeof(char *) * (i));
// 	if (! info->env)
// 		return ;
// 	store_env_aux(info, env);
// }
