/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:13:12 by amanjon-          #+#    #+#             */
/*   Updated: 2024/02/02 11:20:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// gcc -Wall -Werror -Wextra ../../libft/Libft/src/ft_putstr_fd.c ../utils.c unset.c ../sandbox2.c ../../libft/Libft/src/ft_strtrim.c ../../libft/Libft/src/ft_strjoin.c builtins.c env.c echo.c pwd.c export.c cd.c -o cd && ./cd

/**
 * Replaces the existing environment variable node
 * @param	t_env *envi, char *str
 * @return	void
*/
void	ft_replace_node(t_env *envi, char *str)
{
	t_env	*aux;
	t_env	*node_free;
	t_env	*new_node;
	int		len;

	aux = envi;
	node_free = NULL;
	len = 0;
	while (str[len] != '=')
		len++;
	while (aux)
	{
		if (ft_strncmp(aux->content, str, len + 1) == 0)
		{
			node_free = aux;
			aux = aux->prev;
			new_node = ft_lstnew_str_env(str);
			new_node->next = aux->next->next;
			aux->next = new_node;
			ft_lstdelone_ms(node_free, &dele);
			break;
		}
		aux = aux->next;
	}
	ft_print_lst_2(envi); // solo para check
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
	// char cwd[PATH:MAX];
	char cwd[1024];
	
	envi->pwd = getcwd(cwd, sizeof(cwd));
	printf("PWD antes del cambio  = %s\n", cwd);
	printf("envi->pwd = %s\n", envi->pwd);

	change = chdir(path);
	printf("change = %d\n", change);
	
	envi->old_pwd = getcwd(cwd, sizeof(cwd));
    printf("PWD despues del cambio  = %s\n", cwd);
	printf("envi->old_pwd = %s\n", envi->old_pwd);
	
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

void	ft_update_env_pwd(t_env *envi, char *pwd, char *old_pwd)
{
	printf("PWD=%s\n", pwd);
	printf("OLDPWD=%s\n", old_pwd);
	// if (old_pwd == NULL)
	// 	old_pwd = ft_find_path_env(envi, "OLDPWD=");
	if (pwd != NULL)
	{
		ft_replace_node(envi, pwd);
		ft_print_lst_2(envi);
	}
}

void	ft_cd(char **cmd, t_env *envi)
{
	char	*path_home;
	int		ok_change_dir;
	// char	cwd[1024];

	path_home = NULL;
	ok_change_dir = 0;
	if (cmd[1] != NULL)
	{
		// printf("envi->old_pwd = %s\n", envi->old_pwd);
		// getcwd(cwd, sizeof(cwd));
		// printf("PWD antes del cambio ******* = %s\n", cwd);;

		ok_change_dir = ft_change_directory(envi, cmd[1]);		// cd /Users/amanjon-/Desktop/minishell_github/src/ --> 1 argv 
	
		// printf("envi->pwd = %s\n", envi->pwd);
		// getcwd(cwd, sizeof(cwd));
   		// printf("PWD despues del cambio******* = %s\n", cwd);
	}
	else
	{
		path_home= ft_find_path_env(envi, "HOME=");		//	cd NULL --> cambio al HOME=/Users/amanjon-
		ft_change_directory(envi, path_home);
	}
	if (!ok_change_dir)
	{

		ft_update_env_pwd(envi, "PWD=", "OLDPWD=");	// Si se ha podido cambiar de drectorio,actualizo el PWD y el OLDPWD.
	}
}

int main(int argc, char **argv, char **env)
{
	t_env	*envi;
	char	*cmd[3];
    (void) 	argc;
    (void) 	argv;

	ft_linked_list_env(&envi, env);
	envi->pwd = NULL;
	envi->old_pwd = NULL;
	cmd[0] = "cd";
	// cmd[1] = "..";		// Creo que no hay que hacerlo
	// cmd[1] = "/Users/amanjon-/Desktop/minishell_github/src/";
	// cmd[1] = "/Users/amanjon-/Desktop/minishell_github/sraaac/";
	cmd[1] = "/home/amanjon-/Escritorio";		//Linux
	// cmd[1] = NULL;
	
	ft_builtins(cmd, envi);
	return (0);
}

// cd /Users/amanjon-/Desktop/minishell_github/		(ruta absoluta)
// cd ..				(ruta relativa)
// cd builtins.c/		¿(ruta relativa)?