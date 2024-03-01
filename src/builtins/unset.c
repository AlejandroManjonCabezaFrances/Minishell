/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:13:17 by amanjon-          #+#    #+#             */
/*   Updated: 2024/03/01 14:05:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// gcc -Wall -Werror -Wextra ../../libft/Libft/src/ft_putstr_fd.c ../utils.c unset.c ../sandbox2.c ../../libft/Libft/src/ft_strtrim.c ../../libft/Libft/src/ft_strjoin.c builtins.c env.c echo.c exit.c pwd.c export.c cd.c -o unset && ./unset

// ################ env -i ./minishell ######################
// gcc -Wall -Werror -Wextra ../../libft/Libft/src/ft_putstr_fd.c ../utils.c unset.c ../sandbox2.c ../../libft/Libft/src/ft_strtrim.c ../../libft/Libft/src/ft_strjoin.c builtins.c env.c echo.c exit.c pwd.c export.c cd.c -o unset && env -i ./unset
// ################ env -i ./minishell ######################

void	ft_handle_list_header_and_tail(t_env **envi, t_env **aux)
{
	t_env	*temp;
	t_env	*last_node;

	temp = *envi;
	last_node = ft_lstlast_ms(temp);
	if (*aux != *envi)		// no primer nodo lista
	{
		*aux = (*aux)->prev;
		if ((*aux)->next != last_node)	//	lista media
		{
			(*aux)->next = (*aux)->next->next;
			(*aux)->next->prev = (*aux);
		}
		else							// ultimo node lista
		(*aux)->next = (*aux)->next->next;
		
	}
	else									//	primer nodo lista
	{
		*envi = (*envi)->next;
		// *aux = *envi;
	}
}

void	ft_delete_node(t_env *envi, char *cmd)
{
	t_env	*aux;
	t_env	*node_free;
	int		len;

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
			ft_handle_list_header_and_tail(&envi, &aux);
			ft_lstdelone_ms(node_free, &dele);
		}
		aux = aux->next;
	}
	ft_print_lst_2(envi); // print para checkear
	printf("***********\n\n");
}

void	ft_unset(char **cmd, t_env *envi)
{
	int i;

	i = 1;
	if (*cmd == NULL || cmd == NULL)
		return ;
	while (cmd[i])
	{
		ft_delete_node(envi, cmd[i]);
		i++;
	}
	// ft_print_lst_2(envi);
}

// int main(int argc, char **argv, char **env)
// {
// 	t_env *envi;

// 	envi = NULL;

// 	if (*env == NULL)
// 	{
// 		ft_simulate_env_i_minishell(&envi);
// 	}
// 	// ################ env -i ./minishell ######################
// 	else
// 	{
// 		ft_linked_list_env(&envi, env);
// 	}
	
// 	ft_linked_list_env(&envi, env);
//     (void) argc;
//     (void) argv;
// 	/* ejemplo --> primer variable env en Linux */	
// 	// char *cmd[3];
// 	// cmd[0] = "unset";
// 	// cmd[1] = "HOSTTYPE";
// 	// cmd[2] = NULL;

// 	/* ejemplo --> penúltima variable env en Linux*/
// 	// char *cmd[3];
// 	// cmd[0] = "unset";
// 	// cmd[1] = "PATH";
// 	// cmd[2] = NULL;

// 	/* ejemplo --> última variable env en Linux*/
// 	// char *cmd[3];
// 	// cmd[0] = "unset";
// 	// cmd[1] = "_";
// 	// cmd[2] = NULL;
	
// 	// char *cmd[4];
// 	// cmd[0] = "unset";
// 	// cmd[1] = "PWD";
// 	// cmd[2] = "OLDPWD";
// 	// cmd[3] = NULL;
// 	// tratado como dos argumentos separados--> unset PWD OLDPWD
	
// 	// char *cmd[4];
// 	// cmd[0] = "unset";
// 	// cmd[1] = "SHLVL";
// 	// cmd[2] = "ZSH";
// 	// cmd[3] = NULL;
	
// 	// char *cmd[2];
	
// 	// cmd[0] = "4";
// 	// cmd[1] = NULL;
// 	// cmd[0] = "";
// 	// cmd[1] = NULL;
// 	// cmd[0] = "unset";
// 	// cmd[1] = NULL;
// 	ft_builtins(cmd, envi, env);
// 	ft_print_lst_2(envi);
// 	return (0);
// }



// ** FALLO PRIMER NODO DE LA LISTA **
	/* ejemplo --> primer variable env en Linux */	
		// char *cmd[3];
		// cmd[0] = "unset";
		// cmd[1] = "HOSTTYPE";
		// cmd[2] = NULL;

// ** FALLO cuando env -i ./minishell, ya que el primer nodo será PWD **
		// char *cmd[4];
	// cmd[0] = "unset";
	// cmd[1] = "PWD";
	// cmd[2] = "OLDPWD";
	// cmd[3] = NULL;
