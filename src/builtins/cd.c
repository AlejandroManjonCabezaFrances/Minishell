/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:13:12 by amanjon-          #+#    #+#             */
/*   Updated: 2024/02/23 12:56:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// gcc -Wall -Werror -Wextra ../../libft/Libft/src/ft_putstr_fd.c ../utils.c unset.c ../sandbox2.c ../../libft/Libft/src/ft_strtrim.c ../../libft/Libft/src/ft_strjoin.c builtins.c env.c echo.c exit.c pwd.c export.c cd.c -o cd && ./cd

// ################ env -i ./minishell ######################
// gcc -Wall -Werror -Wextra ../../libft/Libft/src/ft_putstr_fd.c ../utils.c unset.c ../sandbox2.c ../../libft/Libft/src/ft_strtrim.c ../../libft/Libft/src/ft_strjoin.c builtins.c env.c echo.c exit.c pwd.c export.c cd.c -o cd && env -i ./cd
// ################ env -i ./minishell ######################


/**
 * Replaces the pwd of the linked list when --> env -i ./minishell
 * @param	t_env **envi, char *str, char *pwd_oldpwd
 * @return	void
*/
void	ft_pwd_without_env(t_env **envi, char *str, char *pwd_oldpwd)
{
	t_env	*aux;
	t_env	*node_free;
	t_env	*new_node;
	char	*result_join;
	
	aux = *envi;
	node_free = NULL;
	result_join = NULL;
	node_free = aux;
	result_join = ft_strjoin(str, pwd_oldpwd); 
	new_node = ft_lstnew_str_env(result_join);
	free(result_join);
	*envi = new_node;
	new_node->next = aux->next;
	(*envi)->next = aux->next;
	(*envi)->next->prev = new_node;
	new_node->prev = NULL;
	ft_lstdelone_ms(node_free, &dele);
}

/**
 * Replaces the oldpwd of the linked list when --> env -i ./minishell
 * @param	t_env *aux, char *str, char *pwd_oldpwd
 * @return	void
*/
void	ft_oldpwd_without_env(t_env *aux, char *str, char *pwd_oldpwd)
{
	t_env	*node_free;
	t_env	*new_node;
	char	*result_join;
	
	node_free = NULL;
	node_free = aux;
	result_join = NULL;
	aux = aux->prev;
	result_join = ft_strjoin(str, pwd_oldpwd);
	new_node = ft_lstnew_str_env(result_join);
	free(result_join);
	if (aux->next->next != NULL)
		aux->next->next->prev = new_node;
	new_node->next = aux->next->next;
	aux->next = new_node;
	new_node->prev = aux;
	ft_lstdelone_ms(node_free, &dele);
}

/**
 * Replaces the environment variables that this function receives as arguments
 * @param	t_env **envi, char *str, char *pwd_oldpwd
 * @return	void
*/
void	ft_replace_node_tail_header(t_env **envi, char *str, char *pwd_oldpwd)
{
	t_env	*aux;
	int		len;

	aux = *envi;
	len = 0;
	while (str[len] != '=')
		len++;
	while (aux)
	{
		if (ft_strncmp(aux->content, str, len + 1) == 0)
		{
			if (aux == *envi)
				ft_pwd_without_env(envi, str, pwd_oldpwd);
			else
				ft_oldpwd_without_env(aux, str, pwd_oldpwd);
			break;
		}
		aux = aux->next;
	}
	ft_print_lst_2(*envi); // solo para check
}

/**
 * int chdir(const char *path); Check the path of the directory you want to change to.
 * @param	char *path, char **env_cpy
 * @return	int. corresponds to the correct or incorrect change of the path
 * 
*/
int	ft_change_directory(t_env *envi, char *path)
{
	int change;
	char cwd[PATH_MAX];
	
	envi->old_pwd = ft_strdup(getcwd(cwd, sizeof(cwd)));
	change = chdir(path);
	envi->pwd = getcwd(cwd, sizeof(cwd));
	if (change != 0)
		perror(path);
	return (change);
}

/**
 * We look for the content of the environment variable "HOME="
 * @param	t_env *envi, char *str
 * @return	char. NULL or the content of HOME=
*/
char	*ft_find_path_env(t_env *envi, char *str)
{
	t_env	*aux;
	int 	len;

	aux = envi;
	len = ft_strlen(str);
	while (aux)
	{
		if (ft_strncmp(aux->content, str, len) == 0)
		{
			return (aux->content + len);
		}
		aux = aux->next;	
	}
	return (NULL);
}

/**
 * Updates the env with its corresponding PWD and OLDPWD
 * @param	t_env *envi
 * @return	void
*/
void	ft_update_env_pwd_oldpwd(t_env *envi)
{
	if (envi->flag == 1)
	{
		ft_replace_node_tail_header(&envi, "OLDPWD=", envi->old_pwd);
		ft_replace_node_tail_header(&envi, "PWD=", envi->pwd);
	}
	else
	{
		ft_replace_node(envi, "OLDPWD=", envi->old_pwd);
		ft_replace_node(envi, "PWD=", envi->pwd);
	}
		
}

/**
 * Updates PWD and OLDPWD variables
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
	envi->old_pwd = ft_strdup(getcwd(cwd, sizeof(cwd))); // creo que no hace falta crear flag xra no entre aqui si estoy con simulacion env -i
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
	envi->pwd = getcwd(cwd, sizeof(cwd));
	if (change != 0)
		perror(cd_back);
	free(cd_back);
	return (change);
}

/**
 * Adds a node to the end of the env linked list
 * @param	t_env *envi
 * @return	void
*/
void	ft_add_node_tail_lst(t_env *envi)
{
	char cwd[PATH_MAX];
	char	*node_oldpwd;
	
	node_oldpwd = NULL;
	envi->old_pwd = ft_strdup(getcwd(cwd, sizeof(cwd)));
	node_oldpwd = ft_strjoin("OLDPWD=", envi->old_pwd);
	ft_lstadd_back_str_env(&envi, ft_lstnew_str_env(node_oldpwd));
	free (node_oldpwd);
	ft_print_lst_2(envi);		// check
}

/**
 * Receives a char * and looks for it in the env
 * @param	t_env *envi, char *str
 * @return	int. FALSE or TRUE
*/
int	ft_env_var_existing(t_env *envi, char *str)
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
 * Replicates the "cd" builtin. Checks if the command has argv
 * ('..' or a path) or not (go to home) and updates PWD and OLDPWD of the env
 * @param	char **cmd, t_env *envi
 * @return	void
*/
void	ft_cd(char **cmd, t_env *envi)
{
	char	*path_home;
	int		ok_change_dir;

	path_home = NULL;
	ok_change_dir = 0;
	if (cmd[1] != NULL)		// distinto de NULL
	{
		if (ft_strncmp("..", cmd[1], 2) == 0)	// ..
		{
			if (ft_env_var_existing(envi, "OLDPWD=") == FALSE)		// cuando no existe el OLDPWD en el env
				ft_add_node_tail_lst(envi);
			ft_one_step_back(envi);
		}
		else
			ok_change_dir = ft_change_directory(envi, cmd[1]);	// cd  /home/amanjon-/Escritorio
	}
	else
	{
		path_home= ft_find_path_env(envi, "HOME=");		//	cd NULL --> cambio al HOME=/Users/amanjon-
		ft_change_directory(envi, path_home);
	}
	printf("cd_check\n");
	if (!ok_change_dir)							// actualiza PWD y OLDPWD
		ft_update_env_pwd_oldpwd(envi);
}

void	ft_simulacion_env_i_minishell(t_env **envi)
{
	char	**env_n;
	char	cwd[PATH_MAX];

	env_n = malloc(sizeof(char *) * 4);
	env_n[0] = ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));
	env_n[1] = ft_strdup("SHLVL=1");
	env_n[2] = ft_strdup("_=/usr/bin/env");
	env_n[3] = NULL;
	ft_linked_list_env(envi, env_n);
	(*envi)->flag = 1;
	// ft_print_lst_2(*envi);
}

int main(int argc, char **argv, char **env)
{
	t_env	*envi;
	char	*cmd[3];
    (void) 	argc;
    (void) 	argv;
	(void)	env;

	envi = NULL;
	// ################ env -i ./minishell ######################
	if (*env == NULL)
		ft_simulacion_env_i_minishell(&envi);
	// ################ env -i ./minishell ######################
	else
		ft_linked_list_env(&envi, env);
	envi->pwd = NULL;
	envi->old_pwd = NULL;
	cmd[0] = "cd";
	cmd[1] = "..";
	// cmd[1] = "/Users/amanjon-/Desktop/minishell_github/src/";
// 	// cmd[1] = "/Users/amanjon/Desktop/minishell_github/sraaac/";
// 	// cmd[1] = "/home/amanjon-/Escritorio";		//Linux
// 	cmd[1] = NULL;
	
	ft_builtins(cmd, envi);
	// ft_print_lst_2(envi);
	return (0);
}

// cd /Users/amanjon-/Desktop/minishell_github/		(ruta absoluta)
// cd ..				(ruta relativa)
// cd builtins/		¿(ruta relativa)?