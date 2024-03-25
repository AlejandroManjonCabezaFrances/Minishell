/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:44:58 by amanjon-          #+#    #+#             */
/*   Updated: 2024/03/25 10:38:33 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Create linked list of environment with struct t_env
 * @param	t_env **t_env, char **env
 * @return	void
*/
void	ft_linked_list_env(t_env **envi, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_lstadd_back_str_env(envi, ft_lstnew_str_env(env[i]));
		i++;
	}
}

void	ft_print_lst_2(t_env *temp)
{
	while (temp)
	{
		printf("%s\n", temp->content);
		temp = temp->next;
	}
}

void	ft_print_double_pointer(char **env_array)
{
	int	i;

	i = 0;
	while (env_array[i])
	{
		printf("env_array[%d] = %s\n", i, env_array[i]);
		i++;
	}
}

/**
 * We create a double pointer and simulate the environment variables
 *	when --> env -i ./minishell
 * @param	t_env *envi
 * @return	void
*/
void	ft_simulate_env_i_minishell(t_env **envi, t_info *info)
{
	char	cwd[PATH_MAX];

	info->env_cpy = malloc(sizeof(char *) * 4);
	info->env_cpy[0] = ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));
	info->env_cpy[1] = ft_strdup("SHLVL=1");
	info->env_cpy[2] = ft_strdup("_=/usr/bin/env");
	info->env_cpy[3] = NULL;
	ft_linked_list_env(envi, info->env_cpy);
	(*envi)->flag = 1;
}

/**
 * Compares the two strings it receives and returns something other than 0 if
 * they are different
 * @param	const char *s1, const char *s2
 * @return	int
*/
int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
