/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandbox2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 08:06:13 by amanjon-          #+#    #+#             */
/*   Updated: 2024/01/12 11:17:56 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strjoin_2(char *s1, char *s2)
{
	char	*ptr;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	ptr = malloc(sizeof(char) * (ft_strlen((char *)s1)
				+ft_strlen((char *)s2)) + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
		ptr[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		ptr[j++] = s2[i++];
	ptr[j] = '\0';
	return (ptr);
}

static int	ft_size_mem(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		i++;
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_copy_in_mem(int k, char	*ptr, long n1)
{
	if (n1 == 0)
	{
		ptr[0] = '0';
		return (ptr);
	}
	if (n1 < 0)
	{
		ptr[0] = '-';
		n1 = n1 * (-1);
	}
	k--;
	while (k >= 0 && n1 != 0)
	{
		ptr[k] = n1 % 10 + '0';
		n1 = n1 / 10;
		k--;
	}
	return (ptr);
}

char	*ft_itoa(int nbr)
{
	int		k;
	char	*ptr;
	long	n1;

	n1 = nbr;
	k = ft_size_mem(n1);
	ptr = malloc(sizeof(char) * (k + 1));
	if (ptr == NULL)
		return (NULL);
	ptr[k] = '\0';
	return (ft_copy_in_mem(k, ptr, n1));
}

int	ft_atoi(const char *str)
{
	int	i;
	int	c;
	int	m;

	i = 0;
	c = 0;
	m = 1;
	while (str[i] == ' ' || str[i] == '\f'
		|| str[i] == '\n' || str[i] == '\r' || str[i] == '\t'
		|| str[i] == '\v')
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			m = m * (-1);
		i++;
		break ;
	}
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		c = c * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(c * m));
}

void	ft_print_lst_2(t_env *temp)
{
	while (temp)
	{
		printf("temp = %s\n", temp->content);
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
	node->content = ft_strdup(str_env);
	node->next = NULL;
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
 * Delete one node of linked list
 * @param	t_env *lst, void (*del)(void *)
 * @return	void
*/
void	ft_lstdelone_mshell(t_env *envi/* , void (*del)(void *) */)
{
	if (envi != NULL /* && del != NULL */)
	{
		free(envi->content);
		free(envi);
	}
}




/* ###############   #################    ######################   ############# */
/* ###############   #################    ######################   ############# */
/* ###############   #################    ######################   ############# */
/* ###############   #################    ######################   ############# */

/**
 * Change contained of SHLVL +1
 * @param	t_env **t_env
 * @return	void
*/
void	ft_replace_SHLVL(t_env **envi)
{
	t_env	*aux;
	char	*temp;
	
	aux = *envi;
	temp = NULL;
	while (aux)
	{
		if (ft_strncmp("SHLVL=", aux->content, 6) == 0)
		{
			if (ft_atoi(aux->content + 6) > 0)
			{
				temp = ft_itoa(ft_atoi(aux->content + 6) + 1);
				printf("temp ft_itoaft_atoi = %s\n\n\n", temp);
				aux->content = ft_strjoin_2("SHLVL=", temp);
			}
		}	
		aux = aux->next;
	}
}

/**
 * find and delete variable environment to builtins unset
 * @param	t_env **t_env, const char *var
 * @return	void
*/
void	ft_find_and_delete_variable_env(t_env **envi, const char *var)
{
	t_env *aux;
	t_env *prev;
	size_t var_len;

	aux = *envi;
	prev = NULL;
	var_len = ft_strlen(var);
	while (aux)
	{
		if (ft_strncmp(var, aux->content, var_len) == 0)
		{
			if (prev)
				prev->next = aux->next;
			else
				*envi = aux->next;
			ft_lstdelone_mshell(aux);
			return ;
		}
		prev = aux;
		aux = aux->next;
	}
}

/**
 * Find variable env and returns the content of this variable env 
 * @param	t_env *t_env, const char *var
 * @return	char *
*/
char	*ft_find_content_var_env(t_env *envi, char *var)
{
	int	i;

	i = 0;
	while (envi)
	{
		if (ft_strncmp(var, envi->content, ft_strlen(var)) == 0 && envi->content[ft_strlen(var)] == '=')
			return (envi->content + (ft_strlen(var) + 1));
		envi = envi->next;
	}
	printf("%s: not a valid identifier\n", var);
	return ("ERROR");
}

/**
 * Create linked list of environment
 * @param	t_env **t_env, char **env
 * @return	void
*/
void	ft_linked_list_env(t_env **envi, char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		ft_lstadd_back_str_env(envi, ft_lstnew_str_env(env[i]));
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

/**
 * Convert linked list in a matrix to ´ll use in execve(third argumment);
 * @param	t_env *t_env
 * @return	char **
*/
char	**ft_convert_linked_list_to_array(t_env *envi)
{
	t_env 	*aux;
	char	**env_array;
	int 	env_count;
	int 	i;
	
	aux = envi;
	env_count = 0;
	i = 0;
	while (aux)
	{
		env_count++;
		aux = aux->next;
	}
	env_array = (char **)malloc(sizeof(char *) * (env_count + 1));
	aux = envi;
	while (aux)
	{
		env_array[i] = aux->content;
		i++;
		aux = aux->next;
	}
	env_array[i] = NULL;
	ft_print_double_pointer(env_array);
	
	ft_lstclear_mshell_2(&aux);
	/* free(aux); */
	
	return (env_array);
}

int main(int argc, char **argv, char **env)
{
	(void) 	env;
	(void) 	argv;
	(void)	argc;
	t_env	*envi;
	// char **env_array;

	// if (argc != 2)
	// {
	// 	printf("error: just one argc\n");
	// 	return (-1);
	// }
	
	ft_linked_list_env(&envi, env);		// 1, 2, 3, 4
	
	ft_print_lst_2(envi);			// 2,
	ft_replace_SHLVL(&envi);
	ft_print_lst_2(envi);
	

	// ft_print_lst_2(envi);			// 3
	// printf("\n\n");
	// ft_find_and_delete_variable_env(&envi, argv[1]);
	// ft_print_lst_2(envi);
	
	// ft_print_lst_2(envi);			// 1,
	
	// printf("\n\n");						// 4
	// printf("return -> %s\n", ft_find_content_var_env(envi, argv[1]));
	// printf("\n\n");
	
	// env_array = ft_convert_linked_list_to_array(envi);		//5
	ft_lstclear_mshell_2(&envi);		// 1, 2, 3
	
	return (0);
}
// gcc -Wall -Werror -Wextra env.c sandbox2.c -o run_env && ./run_env PATH