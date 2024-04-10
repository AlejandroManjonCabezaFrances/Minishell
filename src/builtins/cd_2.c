/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:00:36 by amanjon-          #+#    #+#             */
/*   Updated: 2024/03/28 15:00:36 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Updates the env with its corresponding PWD and OLDPWD
 * @param	t_env *envi
 * @return	void
*/
void	ft_update_env_pwd_oldpwd(t_env *envi)
{
	if (envi->flag == 1)
	{
		ft_replace_node_cd(&envi, "PWD=", envi->pwd);
		ft_replace_node_cd(&envi, "OLDPWD=", envi->old_pwd);
	}
	else
	{
		ft_replace_node(envi, "OLDPWD=", envi->old_pwd);
		ft_replace_node(envi, "PWD=", envi->pwd);
	}
}

/**
 * We look for the content of the environment variable "HOME="
 * @param	t_env *envi, char *str
 * @return	char. NULL or the content of HOME=
*/
char	*ft_find_path_env(t_env *envi, char *str)
{
	t_env	*aux;
	int		len;

	aux = envi;
	len = ft_strlen(str);
	while (aux)
	{
		if (ft_strncmp(aux->content, str, len) == 0)
			return (aux->content + len);
		aux = aux->next;
	}
	return (NULL);
}

/**
 * int chdir(const char *path); Check the path of the directory
 * you want to change to.
 * @param	char *path, char **env_cpy
 * @return	int. corresponds to the correct or incorrect change of the path
 * 
*/
int	ft_change_directory(t_env *envi, char *path)
{
	int		change;
	char	cwd[PATH_MAX];

	envi->old_pwd = ft_strdup(getcwd(cwd, sizeof(cwd)));
	change = chdir(path);
	envi->pwd = ft_strdup(getcwd(cwd, sizeof(cwd)));
	if (change != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		g_signal_code = 1;
		perror(path);
		free(envi->old_pwd);
		free(envi->pwd);
	}
	return (change);
}

static void	ft_trim_one_step_back(int change, char *cd_back)
{
	if (change != 0)
		perror(cd_back);
	free(cd_back);
}

/**
 * We reserve memory to update envi->old_pwd and envi->pwd and
 * we return an int to manage whether or not the directory can be changed
 * @param	t_env *envi
 * @return	int
*/
int	ft_one_step_back(t_env *envi)
{
	char	cwd[PATH_MAX];
	char	*last_ocurrence;
	char	*cd_back;
	int		change;
	size_t	len;

	change = -1;
	cd_back = NULL;
	if ((getcwd(cwd, sizeof(cwd))) != NULL)
		envi->old_pwd = ft_strdup(getcwd(cwd, sizeof(cwd)));
	last_ocurrence = ft_strrchr(envi->old_pwd, '/');
	if (last_ocurrence != NULL)
	{
		len = last_ocurrence - envi->old_pwd;
		cd_back = malloc(sizeof(char) * (len + 1));
		if (cd_back == NULL)
			return (0);
		ft_strlcpy(cd_back, envi->old_pwd, len + 1);
	}
	change = chdir(cd_back);
	if ((getcwd(cwd, sizeof(cwd))) != NULL)
		envi->pwd = ft_strdup(getcwd(cwd, sizeof(cwd)));
	ft_trim_one_step_back(change, cd_back);
	return (change);
}
