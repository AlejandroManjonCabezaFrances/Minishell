/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:13:20 by amanjon-          #+#    #+#             */
/*   Updated: 2024/02/16 14:50:21 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// gcc -Wall -Werror -Wextra ../../libft/Libft/src/ft_putstr_fd.c ../utils.c unset.c ../sandbox2.c ../../libft/Libft/src/ft_strtrim.c ../../libft/Libft/src/ft_strjoin.c builtins.c cd.c exit.c env.c echo.c pwd.c export.c -o export && ./export

// void    ft_no_digits_argv(char *str, t_env *envi)
// {
	
// }

void    ft_digits_argv(t_env *envi)
{
	t_env   *aux;
	char	*n_shlvl;
	(void)  envi;
	
	aux = envi;
	n_shlvl = NULL;
	ft_putendl_fd("exit", 1);
	while (aux)
	{
		if (ft_strncmp(aux->content, "SHLVL=", 6) == 0)
		{
			n_shlvl = ft_itoa((ft_atoi(aux->content + 6) - 1));
			printf("n_shlvl = %s\n", n_shlvl);
			ft_replace_node(envi, "SHLVL=", n_shlvl);
			free(n_shlvl);
		}
		aux = aux->next;
	}
	ft_print_lst_2(envi);
}

void    ft_exit(char **cmd, t_env *envi)
{
	if (cmd[1] == NULL || ft_isdigit(*cmd[1]))
		ft_digits_argv(envi);
	// else
	//     ft_no_digits_argv(cmd[1], envi);
}

int main(int argc, char **argv, char **env)
{
	t_env   *envi;
	(void) 	argc;
	(void) 	argv;
	char    *cmd[2];

	envi = NULL;
	ft_linked_list_env(&envi, env);
	
	cmd[0] = "exit";
	cmd[1] = NULL;
	// cmd[1] = "1";
	
	// cmd[1] = "a";
	// cmd[1] = ".";
	
	ft_builtins(cmd, envi);
	
	return (0);
}
