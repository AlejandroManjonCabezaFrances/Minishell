/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:13:12 by amanjon-          #+#    #+#             */
/*   Updated: 2024/01/31 11:40:59 by marvin           ###   ########.fr       */
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
    printf("%s\n", cwd); 
	
	// if (change != 0)
	// 	perror(path);
}

void	ft_cd(char **cmd, char **env_cpy)
{
	if (cmd[2] != NULL)
		ft_change_directory(cmd[2], env_cpy);
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
	// cmd[2] = "/Users/amanjon-/Desktop/minishell_github/src/";
	// cmd[2] = "/Users/amanjon-/Desktop/minishell_github/sraaac/";
	// cmd[2] = "/home/amanjon/minishell_github/src/builtins/";		//Linux
	cmd[2] = "/home/amanjon/minishell_github/";		//Linux
	
	ft_builtins(cmd, env_cpy);
	return (0);
}

// cd /Users/amanjon-/Desktop/minishell_github/		(ruta absoluta)
// cd ..				(ruta relativa)
// cd builtins.c/		¿(ruta relativa)?