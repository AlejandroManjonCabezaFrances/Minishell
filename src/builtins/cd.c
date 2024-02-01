/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:13:12 by amanjon-          #+#    #+#             */
/*   Updated: 2024/02/01 10:49:08 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// gcc -Wall -Werror -Wextra ../../libft/Libft/src/ft_putstr_fd.c ../utils.c unset.c ../sandbox2.c ../../libft/Libft/src/ft_strtrim.c ../../libft/Libft/src/ft_strjoin.c builtins.c echo.c pwd.c export.c cd.c -o cd && ./cd

/**
 * int chdir(const char *path); Check the path of the directory you want to change to.
 * @param	char *path, char **env_cpy
 * @return	void
*/
int	ft_change_directory(char *path)
{
	int change;
	char cwd[PATH_MAX];
	
	change = chdir(path);
	printf("change = %d\n", change);
	
	getcwd(cwd, sizeof(cwd));
    printf("PWD al cambiar  = %s\n", cwd);
	
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
	// t_env	*aux;

	// aux = envi;
	printf("PWD=%s\n", pwd);
	printf("OLDPWD=%s\n", old_pwd);
	if (old_pwd == NULL)
		old_pwd = ft_find_path_env(envi, "OLDPWD=");
	if (old_pwd != NULL)
	{
		ft_print_lst_2(envi);
	}
}

void	ft_cd(char **cmd, t_env **envi)
{
	// t_env	*envi;
	char	*path_no_argv;
	int		no_change_dir;

	envi = NULL;
	no_change_dir = 0;
	// ft_linked_list_env(&envi, env_cpy);
	if (cmd[1] != NULL)
	{
		no_change_dir = ft_change_directory(cmd[1]);		// cd /Users/amanjon-/Desktop/minishell_github/src/ --> 1 argv 
	}
	else
	{
		path_no_argv = ft_find_path_env(envi, "HOME=");		//	cd NULL --> cambio al HOME=/Users/amanjon-
		ft_change_directory(path_no_argv);
	}
	if (!no_change_dir)
	{
		ft_update_env_pwd(envi, ft_find_path_env(envi, "PWD="),		// Si se ha podido cambiar de drectorio,
			ft_find_path_env(envi, "OLDPWD="));						// actualizo el PWD y el OLDPWD.
	}
	
}

int main(int argc, char **argv, char **env)
{
	t_env	envi;
	char	*cmd[3];
	char	**env_cpy;
    (void) 	argc;
    (void) 	argv;

	env_cpy = NULL;
	env_cpy = copy_env(env);
	ft_linked_list_env(&envi, env);
	cmd[0] = "cd";
	// cmd[1] = "..";
	cmd[1] = "/Users/amanjon-/Desktop/minishell_github/src/";
	// cmd[1] = "/Users/amanjon-/Desktop/minishell_github/sraaac/";
	// cmd[1] = "/home/amanjon/";	 //esta es la direccion con solo "cd"	//Linux
	// cmd[1] = "/home/amanjon/minishell_github/";		//Linux
	// cmd[1] = NULL;
	
	ft_builtins(cmd, &envi);
	return (0);
}

// cd /Users/amanjon-/Desktop/minishell_github/		(ruta absoluta)
// cd ..				(ruta relativa)
// cd builtins.c/		¿(ruta relativa)?