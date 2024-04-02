/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:33:42 by amanjon-          #+#    #+#             */
/*   Updated: 2024/04/02 06:40:02 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * We iterate the list and place the pointer on the last node
 * @param	t_env *lst
 * @return	t_env
*/
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

/**
 * Part of the function that converts the linked list to a double pointer
 * @param	t_env *temp, char **env_array, int *count
 * @return	void
*/
void	ft_convert_list_2(t_env *temp, char **env_array, int *count)
{
	int	i;

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
			break ;
		}
		temp = temp->next;
		(*count)++;
	}
}

/**
 * Function that converts the linked list to a double pointer
 * @param	t_env **envi
 * @return	char **env_array
*/
char	**ft_convert_list_to_double_pointer(t_env **envi)
{
	t_env	*temp;
	char	**env_array;
	int		count;

	temp = *envi;
	count = 0;
	while (temp)
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
	env_array[count] = NULL;
	return (env_array);
}
