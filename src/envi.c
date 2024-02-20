/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:23:02 by amanjon-          #+#    #+#             */
/*   Updated: 2024/02/20 17:31:07 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// ################ env -i ./minishell ######################
void	ft_when_env_is_null(t_env *envi, t_inf *info)
{
	// t_env	*aux;
	(void) info;
	
	envi->env_n = ft_calloc(3, sizeof(char *));
	envi->env_n[0] = ft_strjoin("PWD=", getcwd(info->cwd, sizeof(info->cwd)));
	envi->env_n[1] = ft_strdup("SHLVL=1");
	envi->env_n[2] = ft_strdup("_=/usr/bin/env");
	envi->env_n[3] = NULL;
	// int i;

	// i = 0;
	// while (envi->env_n[i])
	// {
	// 	printf("envi->env_n[%d] = %s\n", i, envi->env_n[i]); 
	// 	i++;
	// }
	// ft_linked_list_env(&envi, envi->env_n);
	// if (aux == NULL)
	// 	printf("envi es NULLLLLL\n");
	// else
	// {
	// 	printf("else**********\n");
	// 	while (aux)
	// 	{
	// 		printf("envi->content = %s\n", aux->content);
	// 		aux = aux->next;
	// 	}
	// 	ft_print_lst_2(envi);
	// }
	// printf("envi->env_n[0] = %s\n", envi->env_n[0]);
	// printf("envi->env_n[1] = %s\n", envi->env_n[1]);
	// printf("envi->env_n[2] = %s\n", envi->env_n[2]);
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

// void	ft_env_is_null(t_inf *info, char **env)
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

void	ft_env_is_null(t_env *envi, t_inf *info, char **env)
{
	// (void)	envi;
	(void)	env;
	
	// envi = NULL;
	int i;
	
	i = 0;
	ft_when_env_is_null(envi, info);

	
}
