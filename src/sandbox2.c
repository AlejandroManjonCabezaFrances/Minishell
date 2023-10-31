/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandbox2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 08:06:13 by amanjon-          #+#    #+#             */
/*   Updated: 2023/10/31 15:38:48 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_print_lst_2(t_env *temp)
{
	while (temp)
	{
		printf("temp = %s\n", temp->env_item);
		temp = temp->next;
	}
}

void	ft_lstclear_mshell_2(t_env **lst)
{
	t_env	*aux;

	while (*lst)
	{
		aux = (*lst)->next;
		free(*lst);
		(*lst) = aux;
	}
	*lst = NULL;
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char	*s1)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (ptr == NULL)
		return (NULL);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}


t_env	*ft_lstnew_str_env(char *str_env)
{
	t_env	*node;

	node = NULL;
	node = malloc(sizeof(t_env));
	if (node == NULL)
		return (NULL);
	node->env_item = ft_strdup(str_env);
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
	}
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}












/**
 * Find variable env and returns the content of this environment variable 
 * @param	t_env *env_copy, const char *var
 * @return	char *
*/
char	*ft_find_variable_env(t_env *env_copy, const char *var)
{
	int	i;

	i = 0;
	while (env_copy)
	{
		if (ft_strncmp(var, env_copy->env_item, ft_strlen(var)) == 0)
			return (env_copy->env_item + (ft_strlen(var) + 1));
		env_copy = env_copy->next;
	}
	return (0);
}

/**
 * Create linked list of environment
 * @param	t_env **env_copy, char **env
 * @return	void
*/
void	ft_linked_list_env(t_env **env_copy, char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		ft_lstadd_back_str_env(env_copy, ft_lstnew_str_env(env[i]));
		i++;	
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

// no debería usar memoria dinámica porque las modificaciones las haré en la 
// lista enlazada, y luego o copiaré tal cual en la matriz para pasarla al execve();
/**
 * Convert linked list in a matrix to ´ll use in execve(third argumment);
 * @param	t_env *env_copy
 * @return	char **
*/
char	**ft_convert_linked_list_to_array(t_env *env_copy)
{
	t_env 	*aux;
	char	**env_array;
	int 	env_count;
	int 	i;
	
	aux = env_copy;
	env_count = 0;
	i = 0;
	while (aux)
	{
		env_count++;
		aux = aux->next;
	}
	env_array = (char **)malloc(sizeof(char *) * (env_count + 1));
	aux = env_copy;
	while (aux)
	{
		env_array[i] = /* ft_strdup( */aux->env_item/* ) */;
		i++;
		aux = aux->next;
	}
	env_array[i] = NULL;
	ft_print_double_pointer(env_array);
	
	ft_lstclear_mshell_2(&aux);
	
	return (env_array);
}

int main(int argc, char **argv, char **env)
{
	(void) env;
	(void) argv;
	t_env	*env_copy;
	char	**env_array;
	int 	i;
	
	i = 0;
	env_copy = NULL;
	if (argc != 2)
	{
		printf("error: just one argc");
		return (-1);
	}	
	ft_linked_list_env(&env_copy, env);
	ft_print_lst_2(env_copy);
	printf("\n\n");
	printf("return -> %s\n", ft_find_variable_env(env_copy, argv[1]));
	printf("\n\n");
	env_array = ft_convert_linked_list_to_array(env_copy);
	while (env_array[i])
	{
		printf("env_array[%d] = %s\n", i, env_array[i]);
		i++;
	}
	ft_lstclear_mshell_2(&env_copy);
	return (0);
}
// gcc -Wall -Werror -Wextra env.c -o run_env && ./run_env PATH