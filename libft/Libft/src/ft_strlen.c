/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:43:34 by amanjon-          #+#    #+#             */
/*   Updated: 2024/04/08 08:09:27 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (str)
		while (str[i] != '\0')
			i++;
	return (i);
}

/* int	main(void)
{
	char	str[] = "holas  ";  //devuelve 7, no cuenta el NULL, pero si espacios
	printf("%zu", ft_strlen(str));
	return (0);
} */
