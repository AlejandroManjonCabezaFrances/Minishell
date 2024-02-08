/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:13:17 by amanjon-          #+#    #+#             */
/*   Updated: 2024/02/07 20:51:05 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// gcc -Wall -Werror -Wextra ../../libft/Libft/src/ft_putstr_fd.c ../utils.c unset.c ../sandbox2.c ../../libft/Libft/src/ft_strtrim.c ../../libft/Libft/src/ft_strjoin.c builtins.c echo.c env.c pwd.c export.c -o unset && ./unset

// printf("aux->next = %s\n", aux->next->content);
// printf("aux->next->next = %s\n", aux->next->next->content);
void	ft_handle_list_header(t_env **envi, t_env **aux)
{
	t_env	*temp;

	temp = NULL;
	if (*aux != *envi)
	{
		*aux = (*aux)->prev;
		temp = *aux;
		(*aux)->next = (*aux)->next->next;
		(*aux)->next->prev = temp;
	}
	else
	{
		*envi = (*envi)->next;
		*aux = *envi;
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
			ft_lstdelone_ms(node_free, &dele);
		}
		aux = aux->next;
	}
	ft_print_lst_2(envi); // print para checkear
	printf("\n\n\n\n");
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
		ft_delete_node(envi, cmd[i]);
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
	// cmd[1] = "SECURITYSESSIONID";
	// cmd[2] = NULL;

	/* ejemplo --> penúltima variable env en Linux*/
	// char *cmd[3];
	// cmd[0] = "unset";
	// cmd[1] = "PATH";
	// cmd[2] = NULL;

	/* ejemplo --> última variable env en Linux*/
	// char *cmd[3];
	// cmd[0] = "unset";
	// cmd[1] = "_";
	// cmd[2] = NULL;
	
	char *cmd[4];
	cmd[0] = "unset";
	cmd[1] = "PWD";
	cmd[2] = "OLDPWD";
	cmd[3] = NULL;
	// tratado como dos argumentos separados--> unset PWD OLDPWD
	
	// char *cmd[4];
	// cmd[0] = "unset";
	// cmd[1] = "SHLVL";
	// cmd[2] = "ZSH";
	// cmd[3] = NULL;
	
	// char *cmd[4];
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
// SEGV  al borrar el ultimo nodo y al pasar numeros /ejemplo de los NULL 's
