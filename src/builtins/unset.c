/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:13:17 by amanjon-          #+#    #+#             */
/*   Updated: 2024/02/06 15:52:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// gcc -Wall -Werror -Wextra ../../libft/Libft/src/ft_putstr_fd.c ../utils.c unset.c ../sandbox2.c ../../libft/Libft/src/ft_strtrim.c ../../libft/Libft/src/ft_strjoin.c builtins.c echo.c env.c pwd.c export.c -o unset && ./unset

// printf("aux->next = %s\n", aux->next->content);
// printf("aux->next->next = %s\n", aux->next->next->content);
void	ft_handle_list_header(t_env **envi, t_env **aux)
{
	if (*aux != *envi)
		*aux = (*aux)->prev;
	else
	{
		*envi = (*aux)->next;
		*aux = (*aux)->next;
	}
}

void	ft_delete_node(t_env *envi, char *cmd)
{
	t_env	*aux;
	t_env	*node_free;
	int		len;

	aux = NULL;
	aux = envi;
	node_free = NULL;
	while (aux)
	{
		len = 0;
		while (aux->content[len] != '=')
			len++;
		if (ft_strncmp(cmd, aux->content, len) == 0)
		{
			node_free = aux;
			ft_handle_list_header(&envi, &aux);
			// if (aux->next != NULL && aux->next->next != NULL)
			aux->next = aux->next->next;
			ft_lstdelone_ms(node_free, &dele);
		}
		aux = aux->next;
	}
	 ft_print_lst_2(envi); // print para checkear
}

void	ft_unset(char **cmd, t_env *envi)
{
	int i;

	i = 1;
	if (*cmd == NULL || cmd == NULL)
		return ;
	else if (cmd[1][0] == 0)
		return ;
	while (cmd[i])
	{
		printf("cmd[%d] = %s\n", i, cmd[i]);
		ft_delete_node(envi, cmd[i]);
		printf("ft_unset_1\n");
		i++;
	}
}

int main(int argc, char **argv, char **env)
{
	t_env *envi;

	envi = NULL;
	ft_linked_list_env(&envi, env);
    (void) argc;
    (void) argv;
	
	/* ejemplo --> primer variable env en Linux */
	// char *cmd[3];
	// cmd[0] = "unset";
	// cmd[1] = "HOSTTYPE";
	// cmd[2] = NULL;

	/* ejemplo --> penúltima variable env en Linux*/
	// char *cmd[3];
	// cmd[0] = "unset";
	// cmd[1] = "INFOPATH";
	// cmd[2] = NULL;

	/* ejemplo --> última variable env en Linux*/
	// char *cmd[3];
	// cmd[0] = "unset";
	// cmd[1] = "_";
	// cmd[2] = NULL;
	
	char *cmd[3];
	cmd[0] = "unset";
	cmd[1] = "PWD";
	cmd[2] = "OLDPWD";
	cmd[3] = NULL;
	// tratado como dos argumentos separados--> unset PWD OLDPWD
	
	// cmd[1] = "4";
	// cmd[2] = NULL;
	// cmd[1] = "";
	// cmd[2] = NULL;
	ft_builtins(cmd, envi);
	// ft_print_lst_2(envi);
	return (0);
}
// Recibe doble puntero ya spliteado
// Checkear el borrado de dos variables de entorno en diferentes argumentos
// SEGV al intentar borrar dos variables a la vez
