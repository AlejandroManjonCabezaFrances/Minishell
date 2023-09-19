/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:48:12 by amanjon-          #+#    #+#             */
/*   Updated: 2023/05/12 07:23:32 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
	{
		free(ptr);
		return (NULL);
	}
	ft_bzero(ptr, count * size);
	return (ptr);
}

/*int main(void)
{
	return (0);
}*/
