/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:31:16 by vini              #+#    #+#             */
/*   Updated: 2024/04/16 11:20:46 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**copy_env(char **envp)
{
	char	**env_cpy;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	env_cpy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env_cpy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env_cpy[i] = ft_strdup(envp[i]);
		i++;
	}
	env_cpy[i] = NULL;
	return (env_cpy);
}

char	*get_path(char **env)
{
	char	*path;

	path = find_var("PATH", env);
	if (!path)
		return (NULL);
	return (path);
}

char	*find_var(char *varname, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(varname, env[i], ft_strlen(varname))
			&& env[i][ft_strlen(varname)] == '=')
			return (env[i] + (ft_strlen(varname) + 1));
		i++;
	}
	if (!ft_strncmp(varname, "?", ft_strlen(varname)))
		return (ft_itoa(g_signal_code));
	return (NULL);
}

int	ft_find_path(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strncmp(str[i], "PATH", ft_strlen(str[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}
