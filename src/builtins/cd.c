/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:13:12 by amanjon-          #+#    #+#             */
/*   Updated: 2024/01/31 13:33:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// gcc -Wall -Werror -Wextra ../../libft/Libft/src/ft_putstr_fd.c ../utils.c unset.c ../sandbox2.c ../../libft/Libft/src/ft_strtrim.c ../../libft/Libft/src/ft_strjoin.c builtins.c echo.c pwd.c export.c cd.c -o cd && ./cd

/**
 * int chdir(const char *path); Check the path of the directory you want to change to.
 * @param	char *path, char **env_cpy
 * @return	void
*/
void	ft_change_directory(char *path, char **env_cpy)
{
	int change;
	char cwd[PATH_MAX];
	(void) env_cpy;
	
	change = chdir(path);
	printf("change = %d\n", change);
	
	getcwd(cwd, sizeof(cwd));
    printf("PWD current = %s\n", cwd);
	
	if (change != 0)
		perror(path);
}

char	*ft_without_arguments(char **env_cpy)
{
	int 	i;
	char	*str;
	int len;

	i = 0;
	str = "HOME=";
	len = ft_strlen(str);
	while (env_cpy[i])
	{
		if (ft_strncmp(env_cpy[i], str, len) == 0)
		{
			return (env_cpy[i] + len);
		}
		i++;	
	}
	return (NULL);
}

void	ft_cd(char **cmd, char **env_cpy)
{
	char	*path_no_argv;
	if (cmd[1] != NULL)
	{
		ft_change_directory(cmd[1], env_cpy);
	}
	else
	{
		path_no_argv = ft_without_arguments(env_cpy);
		ft_change_directory(path_no_argv, env_cpy);
	}
}

int main(int argc, char **argv, char **env)
{
	char	*cmd[3];
	char	**env_cpy;
    (void) 	argc;
    (void) 	argv;

	env_cpy = NULL;
	env_cpy = copy_env(env);
	cmd[0] = "cd";
	// cmd[1] = "..";
	// cmd[1] = "/Users/amanjon-/Desktop/minishell_github/src/";
	// cmd[1] = "/Users/amanjon-/Desktop/minishell_github/sraaac/";
	// cmd[1] = "/home/amanjon/";	 //esta es la direccion con solo "cd"	//Linux
	// cmd[1] = "/home/amanjon/minishell_github/";		//Linux
	cmd[1] = NULL;
	
	ft_builtins(cmd, env_cpy);
	return (0);
}

// cd /Users/amanjon-/Desktop/minishell_github/		(ruta absoluta)
// cd ..				(ruta relativa)
// cd builtins.c/		¿(ruta relativa)?