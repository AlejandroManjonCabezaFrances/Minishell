/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_alex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:44:58 by amanjon-          #+#    #+#             */
/*   Updated: 2024/03/21 10:28:23 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// /**
//  * We create a double pointer and simulate the environment variables
//  *	when --> env -i ./minishell
//  * @param	t_env *envi
//  * @return	void
// */
// void	ft_simulate_env_i_minishell(t_env **envi, t_env **declare)
// {
// 	char	**env_n;
// 	char	cwd[PATH_MAX];

// 	env_n = malloc(sizeof(char *) * 4);
// 	env_n[0] = ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));
// 	env_n[1] = ft_strdup("SHLVL=1");
// 	env_n[2] = ft_strdup("_=/usr/bin/env");
// 	env_n[3] = NULL;
// 	ft_linked_list_env(envi, env_n);
// 	ft_linked_list_env(declare, env_n);
// 	(*envi)->flag = 1;
// }

/**
 * We create a double pointer and simulate the environment variables
 *	when --> env -i ./minishell
 * @param	t_env *envi
 * @return	void
*/
void	ft_simulate_env_i_minishell(t_env **envi, t_env **declare, t_info *info)
{
	char	cwd[PATH_MAX];

	info->env_cpy = malloc(sizeof(char *) * 4);
	info->env_cpy[0] = ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));
	info->env_cpy[1] = ft_strdup("SHLVL=1");
	info->env_cpy[2] = ft_strdup("_=/usr/bin/env");
	info->env_cpy[3] = NULL;
	ft_linked_list_env(envi, info->env_cpy);
	ft_linked_list_env(declare, info->env_cpy);
	(*envi)->flag = 1;
}

// /**
//  * We create a double pointer and simulate the environment variables
//  *	when --> env -i ./minishell
//  * @param	t_env *envi
//  * @return	void
// */
// void	ft_simulate_env_i_minishell(t_info *info)
// {
// 	char	**env_n;
// 	char	cwd[PATH_MAX];

// 	env_n = malloc(sizeof(char *) * 4);
// 	env_n[0] = ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));
// 	env_n[1] = ft_strdup("SHLVL=1");
// 	env_n[2] = ft_strdup("_=/usr/bin/env");
// 	env_n[3] = NULL;
// 	ft_linked_list_env(&(info->envi), env_n);
// 	ft_linked_list_env(&(info->declare), env_n);
// 	info->env_cpy = copy_env(env_n);
// 	(info->envi)->flag = 1;
// }
/**
 * Replaces the existing environment variable node
 * @param	t_env *envi, char *str, char *pwd_oldpwd
 * @return	void
*/
// void	ft_replace_node(t_env *envi, char *str, char *pwd_oldpwd)
// {
// 	t_env	*aux;
// 	t_env	*aux2;
// 	t_env	*node_free;
// 	t_env	*new_node;
// 	int		len;

// 	aux = envi;
// 	aux2 = NULL;
// 	node_free = NULL;
// 	len = 0;
// 	while (str[len] != '=')
// 		len++;
// 	while (aux)
// 	{
// 		if (ft_strncmp(aux->content, str, len) == 0)
// 		{
// 			node_free = aux;
// 			aux2 = aux->next;
// 			aux = aux->prev;
// 			new_node = ft_lstnew_str_env(ft_strjoin(str, pwd_oldpwd));
// 			aux->next = new_node;
// 			new_node->prev = aux;
// 			if (aux2)
// 			{
// 				aux2->prev = new_node;
// 				new_node->next = aux2;
// 			}
// 			else
// 				new_node->next = NULL;
// 			ft_lstdelone_ms(node_free, &del_ms);
// 			break;
// 		}
// 		aux = aux->next;
// 	}
// 	// ft_print_lst_2(envi); // solo para check
// }

/**
 * Replaces the existing environment variable node
 * @param	t_env *aux, t_env *aux2, t_env *node_free, t_env *new_node
 * @return	void
*/
void	ft_trim(t_env *aux, t_env *aux2, t_env *node_free, t_env *new_node)
{
	aux->next = new_node;
	new_node->prev = aux;
	if (aux2)
	{
		aux2->prev = new_node;
		new_node->next = aux2;
	}
	else
		new_node->next = NULL;
	ft_lstdelone_ms(node_free, &del_ms);
}

/**
 * Replaces the existing environment variable node
 * @param	t_env *envi, char *str, char *pwd_oldpwd
 * @return	void
*/
void	ft_replace_node(t_env *envi, char *str, char *pwd_oldpwd)
{
	t_env	*aux;
	t_env	*aux2;
	t_env	*node_free;
	t_env	*new_node;
	int		len;

	aux = envi;
	aux2 = NULL;
	node_free = NULL;
	len = 0;
	while (str[len] != '=')
		len++;
	while (aux)
	{
		if (ft_strncmp(aux->content, str, len) == 0)
		{
			node_free = aux;
			aux2 = aux->next;
			aux = aux->prev;
			new_node = ft_lstnew_str_env(ft_strjoin(str, pwd_oldpwd));
			ft_trim(aux, aux2, node_free, new_node);
			break;
		}
		aux = aux->next;
	}
}

/**
 * Compares the two strings it receives and returns something other than 0 if
 * they are different
 * @param	const char *s1, const char *s2
 * @return	int
*/
int	ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

/**
 * Create linked list of environment with struct t_env
 * @param	t_env **t_env, char **env
 * @return	void
*/
void ft_linked_list_env(t_env **envi, char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		ft_lstadd_back_str_env(envi, ft_lstnew_str_env(env[i]));
		i++;	
	}
}

void ft_print_lst_2(t_env *temp)
{
	while (temp)
	{
		printf("temp = %s\n", temp->content);
		temp = temp->next;
	}
}

void	ft_print_double_pointer(char **env_array)
{
	int i;
	
	i = 0;
	while (env_array[i])
	{
		printf("env_array[%d] = %s\n", i, env_array[i]);
		i++;
	}
}

void	del_ms(void *content)
{
	free(content);
}

void	ft_lstdelone_ms(t_env *lst, void (*del_ms)(void *))
{
	if (lst != NULL && del_ms != NULL)
	{
		(*del_ms)(lst->content);
		free(lst);
	}
}

// void	del_ms(void *content)
// {
// 	free(content);
// }

// void	ft_lstdelone_ms(t_env **lst, void (*del_ms)(void *))
// {
// 	if (*lst != NULL && del_ms != NULL)
// 	{
// 		free((*lst)->content);
// 		free(*lst);
// 	}
// }

t_env	*ft_lstlast_ms(t_env *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	return (lst);
}

t_env	*ft_lstnew_str_env(char *str_env)
{
	t_env	*node;

	node = NULL;
	node = malloc(sizeof(t_env));
	if (node == NULL)
		return (NULL);
	node->content = ft_strdup(str_env);
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	ft_lstadd_back_str_env(t_env **envi, t_env *node)
{
	t_env	*aux;

	aux = *envi;
	if (*envi == NULL)
	{
		*envi = node;
		return ;
	}
	else
	{
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = node;
		node->prev = aux;
	}
}

void	ft_convert_list_2(t_env *temp, char **env_array, int *count)
{
	int i;

	while (temp)
	{
		env_array[*count] = ft_strdup(temp->content);
		if (env_array[*count] == NULL)
		{
			i = 0;
			while (i < (*count))
			{
				free(env_array[i]);
				i++;
			}
			free(*env_array);
			break;	// checkear si es correcto este break
		}
		temp = temp->next;
		(*count)++;
	}
}
char	**ft_convert_list_to_double_pointer(t_env **envi)
{
	t_env	*temp;
	char	**env_array;
	int		count;
	// int 	i;
	
	temp = *envi;
	count = 0;
	while(temp)
	{
		count++;
		temp = temp->next;
	}
	env_array = malloc(sizeof(char *) * (count + 1));
	if (env_array == NULL)
		return (NULL);
	temp = *envi;
	count = 0;
	ft_convert_list_2(temp, env_array, &count);
	// while (temp)
	// {
	// 	env_array[count] = ft_strdup(temp->content);
	// 	if (env_array[count] == NULL)
	// 	{
	// 		i = 0;
	// 		while (i < count)
	// 		{
	// 			free(env_array[i]);
	// 			i++;
	// 		}
	// 		free(*env_array);
	// 		break;	// checkear si es correcto este break
	// 	}
	// 	temp = temp->next;
	// 	count++;
	// }
	env_array[count] = NULL;
	return (env_array);
}