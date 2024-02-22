/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:13:12 by amanjon-          #+#    #+#             */
/*   Updated: 2024/02/22 16:30:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// gcc -Wall -Werror -Wextra ../../libft/Libft/src/ft_putstr_fd.c ../utils.c unset.c ../sandbox2.c ../../libft/Libft/src/ft_strtrim.c ../../libft/Libft/src/ft_strjoin.c builtins.c env.c echo.c exit.c pwd.c export.c cd.c -o cd && ./cd

// ################ env -i ./minishell ######################
// gcc -Wall -Werror -Wextra ../../libft/Libft/src/ft_putstr_fd.c ../utils.c unset.c ../sandbox2.c ../../libft/Libft/src/ft_strtrim.c ../../libft/Libft/src/ft_strjoin.c builtins.c env.c echo.c exit.c pwd.c export.c cd.c -o cd && env -i ./cd
// ################ env -i ./minishell ######################

/**
 * Replaces the existing environment variable node
 * @param	t_env *envi, char *str
 * @return	void
*/
void	ft_replace_node_tail_header(t_env **envi, char *str, char *pwd_oldpwd)
{
	t_env	*aux;
	t_env	*node_free;
	t_env	*new_node;
	int		len;

	aux = *envi;
	node_free = NULL;
	len = 0;
	while (str[len] != '=')
		len++;
	// printf("envi->old_pwd en funcion arriba = %s\n", (*envi)->old_pwd);
	// printf("envi->pwd en funcion arriba = %s\n", (*envi)->pwd);
	printf("pwd_oldpwd = %s\n", pwd_oldpwd);
	while (aux)
	{
		if (ft_strncmp(aux->content, str, len + 1) == 0)
		{
			if (aux == *envi)
			{
				printf("entra en el if\n");
				node_free = aux;
				new_node = ft_lstnew_str_env(ft_strjoin(str, pwd_oldpwd));
				*envi = new_node;
				new_node->next = aux->next;
				(*envi)->next = aux->next;
				(*envi)->next->prev = new_node;
				new_node->prev = NULL;
				ft_lstdelone_ms(node_free, &dele);
				break;
			}
			else
			{
				printf("entra en el else\n");
				node_free = aux;
				aux = aux->prev;
				new_node = ft_lstnew_str_env(ft_strjoin(str, pwd_oldpwd)); // liberar lo que devuelve strjoin
				printf("4\n");
				if (aux->next->next != NULL)
				{
					printf("aux->next = %s\n", aux->next->content);
					// printf("entra en el if?\n");
					aux->next->next->prev = new_node;
				}
				printf("5\n");
				new_node->next = aux->next->next;
				aux->next = new_node;
				ft_lstdelone_ms(node_free, &dele);
				break;
			}
		}
		aux = aux->next;
	}
	ft_print_lst_2(*envi); // solo para check
}

/**
 * int chdir(const char *path); Check the path of the directory you want to change to.
 * @param	char *path, char **env_cpy
 * @return	void
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

void	ft_update_env_pwd(t_env *envi)
{
	printf("update_1\n");
	ft_replace_node_tail_header(&envi, "PWD=", envi->pwd);
	printf("primera vuelta\n");
	ft_print_lst_2(envi);
	printf("env->pwd = %s\n", envi->pwd);
	// printf("env->old_pwd = %s\n", envi->old_pwd);
	ft_replace_node_tail_header(&envi, "OLDPWD=", envi->old_pwd);
	printf("update_3\n");
}

int	ft_one_step_back(t_env *envi)
{
	char	cwd[PATH_MAX];
	char	*last_ocurrence;
	char	*cd_back;
	int		change;
	size_t	len;

	change = -1;
	cd_back = NULL;
	// envi->old_pwd = ft_strdup(getcwd(cwd, sizeof(cwd)));		// creo que hay que hacer flag para que no entre aqui si estoy con la simulacion env -i
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

void	ft_add_node_tail_lst(t_env *envi)
{
	// char cwd_1[PATH_MAX];
	char cwd_2[PATH_MAX];
	// char	*node_pwd;
	char	*node_oldpwd;
	
	// node_pwd = NULL;
	node_oldpwd = NULL;
	
	// envi->pwd = ft_strdup(getcwd(cwd_1, sizeof(cwd_1)));
	// node_pwd = ft_strjoin("PWD=", envi->pwd);
	
	envi->old_pwd = ft_strdup(getcwd(cwd_2, sizeof(cwd_2)));
	node_oldpwd = ft_strjoin("OLDPWD=", envi->old_pwd);
	ft_lstadd_back_str_env(&envi, ft_lstnew_str_env(node_oldpwd));
	
	// free (node_pwd);
	free (node_oldpwd);
	
	// printf("env->pwd = %s\n", envi->pwd);
	// printf("env->old_pwd = %s\n", envi->old_pwd);
	
	ft_print_lst_2(envi);
}

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

void	ft_cd(char **cmd, t_env *envi)
{
	char	*path_home;
	int		ok_change_dir;

	path_home = NULL;
	ok_change_dir = 0;
	if (ft_env_var_existing(envi, "OLDPWD=") == FALSE)		// cuando no existe el OLDPWD en el env
		ft_add_node_tail_lst(envi);
	if (cmd[1] != NULL)		// distinto de NULL
	{
		if (ft_strncmp("..", cmd[1], 2) == 0)	// ..
			ft_one_step_back(envi);
		else
			ok_change_dir = ft_change_directory(envi, cmd[1]);	// cd  /home/amanjon-/Escritorio
	}
	else
	{
		path_home= ft_find_path_env(envi, "HOME=");		//	cd NULL --> cambio al HOME=/Users/amanjon-
		ft_change_directory(envi, path_home);
	}
	if (!ok_change_dir)							// actualiza PWD y OLDPWD
		ft_update_env_pwd(envi);
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
	// ft_print_lst_2(*envi);
}

int main(int argc, char **argv, char **env)
{
	t_env	*envi;
	char	*cmd[3];
    (void) 	argc;
    (void) 	argv;
	(void)	env;

	// ################ env -i ./minishell ######################
	envi = NULL;
	ft_simulacion_env_i_minishell(&envi);
	// ################ env -i ./minishell ######################


	// envi = NULL;
	// ft_linked_list_env(&envi, env);
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