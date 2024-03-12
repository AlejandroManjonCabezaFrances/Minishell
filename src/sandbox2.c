/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandbox2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 08:06:13 by amanjon-          #+#    #+#             */
/*   Updated: 2024/03/12 08:52:08 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// char	*ft_strjoin_2(char *s1, char *s2)
// {
// 	char	*ptr;
// 	int		i;
// 	int		j;

// 	if (s1 == NULL || s2 == NULL)
// 		return (NULL);
// 	ptr = malloc(sizeof(char) * (ft_strlen((char *)s1)
// 				+ft_strlen((char *)s2)) + 1);
// 	if (ptr == NULL)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (s1[i] != '\0')
// 		ptr[j++] = s1[i++];
// 	i = 0;
// 	while (s2[i] != '\0')
// 		ptr[j++] = s2[i++];
// 	ptr[j] = '\0';
// 	return (ptr);
// }

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

// void	ft_lstadd_penultimate_str_env(t_env **envi, t_env *node)
// {
// 	t_env	*aux;
// 	t_env	*last;

// 	aux = *envi;
// 	last = ft_lstlast_ms(*envi);
// 	if (*envi == NULL)
// 	{
// 		*envi = node;
// 		return ;
// 	}
// 	else
// 	{
// 		while (aux->next->next != NULL)
// 			aux = aux->next;
// 		aux->next = node;
// 		node->next = last;
// 	}
// }

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
				aux->content = ft_strjoin("SHLVL=", temp);
			}
		}	
		aux = aux->next;
	}
}

/**
 * find and delete variable environment to builtins unset.
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
			if (prev != NULL)
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
	// int	i;

	// i = 0;
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



/**
 * Obtener el PWD --> Current working directory
*/
// int main()
// {
// 	char cwd[1024];

// 	cwd[0] = '\0';
// 	if (getcwd(cwd, sizeof(cwd)) != NULL/*  && cwd[0] != '\0' */)
// 		printf("directorio trabajo actual = %s\n", cwd);
// 	else
// 	{
// 		perror(cwd);
// 		return (-1);
// 	}	
// 	return (0);
// }

// // ######## getcwd();--> obtiene/muestra directorio dnde trabaja tu programa. Para el PWD######
// int main() 
// {
//     char cwd[1024]; // Búfer para almacenar la ruta
	
//     if (getcwd(cwd, sizeof(cwd)) != NULL) 
//         printf("Directorio de trabajo actual: %s\n", cwd); 
// 	else 
// 	{
//         perror("Error al obtener el directorio de trabajo actual\n");
//         return (1);
//     }
//     return (0);
// }

// int main(int argc, char **argv, char **env)
// {
// 	(void) 	env;
// 	(void) 	argv;
// 	(void)	argc;
// 	t_env	*envi;

// 	envi = NULL;
// 	// char **env_array;

	// if (argc != 2)
	// {
	// 	printf("error: just one argc\n");
	// 	return (-1);
	// }
	// ft_linked_list_env(&envi, env);		// 1, 2, 3, 4
	// ft_print_lst_2(envi);
	// printf("emtra aqui\n");
	
// 	ft_print_lst_2(envi);			// 2,
// 	ft_replace_SHLVL(&envi);
// 	ft_print_lst_2(envi);
	

// 	// ft_print_lst_2(envi);			// 3
// 	// printf("\n\n");
// 	// ft_find_and_delete_variable_env(&envi, argv[1]);
// 	// ft_print_lst_2(envi);
	
// 	// ft_print_lst_2(envi);			// 1,
	
	// printf("\n\n");						// 4
	// printf("return -> %s\n", ft_find_content_var_env(envi, argv[1]));
	// printf("\n\n");
	
// 	// env_array = ft_convert_linked_list_to_array(envi);		//5
// 	ft_lstclear_mshell_2(&envi);		// 1, 2, 3
	
// 	return (0);
// }
// gcc -Wall -Werror -Wextra sandbox2.c -o run_env && ./run_env PATH