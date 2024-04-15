/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:13:12 by amanjon-          #+#    #+#             */
/*   Updated: 2024/04/15 11:46:17 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Adds a node to the end of the env linked list
 * @param	t_env *envi, char **cmd
 * @return	static void
*/
static	void	ft_add_node_tail_lst(t_env *envi, char **cmd)
{
	char	cwd[PATH_MAX];
	char	*node_oldpwd;

	node_oldpwd = NULL;
	if (ft_strcmp(cmd[1], "..") == 0)
		envi->old_pwd = ft_strdup(getcwd(cwd, sizeof(cwd)));
	node_oldpwd = ft_strjoin("OLDPWD=", envi->old_pwd);
	ft_lstadd_back_str_env(&envi, ft_lstnew_str_env(node_oldpwd));
	free (node_oldpwd);
	free (envi->old_pwd);
}

/**
 * Receives a char * and looks for it in the env
 * @param	t_env *envi, char *str
 * @return	int. FALSE or TRUE
*/
static	int	ft_env_var_existing(t_env *envi, char *str)
{
	t_env	*aux;
	int		len;

	aux = envi;
	len = 0;
	while (str[len])
		len++;
	while (aux)
	{
		if (ft_strncmp(str, aux->content, len) == 0)
			return (TRUE);
		aux = aux->next;
	}
	return (FALSE);
}

/**
 * We manage the cd with arguments ".., folder change and when we
 * do env -i ./minishell"
 * @param	char **cmd, t_env *envi, int ok_change_dir
 * @return	int. ok_change_dir
*/
static	int	ft_cd_with_argv(char **cmd, t_env *envi, int ok_change_dir)
{
	if (ft_strncmp("..", cmd[1], 2) == 0)
	{
		if (ft_env_var_existing(envi, "OLDPWD=") == FALSE)
			ft_add_node_tail_lst(envi, cmd);
		ft_one_step_back(envi);
	}
	else
	{
		ok_change_dir = ft_change_directory(envi, cmd[1]);
		if (!ok_change_dir && ft_env_var_existing(envi, "OLDPWD=") == FALSE)
			ft_add_node_tail_lst(envi, cmd);
	}
	return (ok_change_dir);
}

/**
 * Replicates the "cd" builtin. Checks if the command has argv
 * ('..' or a path) or not (go to home) and updates PWD and OLDPWD of the env
 * with/without env -i ./minishell
 * @param	char **cmd, t_env *envi, char **env
 * @return	int
*/
int	ft_cd(char **cmd, t_env *envi, char **env)
{
	char	*path_home;
	int		ok_change_dir;
	int		ok_change_dir_2;

	path_home = NULL;
	ok_change_dir = 0;
	ok_change_dir_2 = 0;
	if (cmd[1] != NULL)
		ok_change_dir = ft_cd_with_argv(cmd, envi, ok_change_dir);
	else
	{
		if (*env == NULL)
		{
			ft_putstr_fd("minisell: cd: HOME not set\n", 2);
			g_signal_code = 1;
			return (1);
		}
		path_home = ft_find_path_env(envi, "HOME=");
		ok_change_dir_2 = ft_change_directory(envi, path_home);
	}
	if (!ok_change_dir && !ok_change_dir_2)
		ft_update_env_pwd_oldpwd(envi);
	return (0);
}
