/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:44:58 by amanjon-          #+#    #+#             */
/*   Updated: 2024/01/24 09:03:16 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

// t_env	**sort_list(t_env **envi)
// {
// 	int aux;
// 	t_env *temp;

// 	temp = *envi;
// 	while(envi->next != '\0')
// 	{
// 		if(((envi->content, envi->next->content)) == 0)
// 		{
// 			aux = envi->content;
// 			envi->content = envi->next->content;
// 			envi->next->content = aux;
// 			envi = temp;
// 		}
// 		else
// 			envi = envi->next;
// 	}
// 	envi = temp;
// 	return (envi);
// }