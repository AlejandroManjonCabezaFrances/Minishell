/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:13:17 by amanjon-          #+#    #+#             */
/*   Updated: 2024/01/29 15:24:44 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// gcc -Wall -Werror -Wextra ../../libft/Libft/src/ft_putstr_fd.c ../utils.c ../sandbox2.c ../../libft/Libft/src/ft_strtrim.c ../../libft/Libft/src/ft_strjoin.c builtins.c echo.c pwd.c unset.c ../utils.c export.c -o unset && ./unset

void	ft_delete_node(t_env **envi, char *cmd)
{
	t_env	*aux;
	t_env	*node_free;
	int		len;
	int		i;

	aux = *envi;
	node_free = NULL;
	i = 0;
	while (cmd[i] == ' ')
		i++;
	while (aux)
	{
		len = 0;
		while (aux->content[len] != '=')
			len++;
		if (ft_strncmp(cmd, aux->content, len) == 0)
		{
			node_free = aux;
			aux = aux->prev;
			aux->next = aux->next->next;
			ft_lstdelone_ms(node_free, &dele);
		}
		aux = aux->next;
		i++;
	}
	ft_print_lst_2(*envi);
}

void	ft_unset(char **cmd, char **env_cpy)
{
	t_env *envi;
	int i;

	envi = NULL;
	i = 0;
	ft_linked_list_env(&envi, env_cpy);
	if (*cmd == NULL)
		return ;
	while (cmd[1][i])
	{
		if (ft_isalpha(cmd[1][i]) == 1)
			ft_delete_node(&envi, cmd[1]);
		break;
		i++;
	}
}

int main(int argc, char **argv, char **env)
{
	char *cmd[3];
	char	**env_cpy;
    (void) argc;
    (void) argv;
    
	env_cpy = NULL;
	env_cpy = copy_env(env);
	cmd[0] = "unset";
	cmd[1] = "PWD";
	// cmd[1] = "4";
	// cmd[1] = "";
	ft_builtins(cmd, env_cpy);
	
	return (0);
}