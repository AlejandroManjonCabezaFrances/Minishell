/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:47:55 by amanjon-          #+#    #+#             */
/*   Updated: 2024/02/26 12:19:35 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
//Tiene que copiarlo a dest y devolver la longuitud string de src
//Si destsize es < que longuitud de src, tiene que retornar longuitud total src

size_t	ft_strlcpy(char *dest, const char *src, size_t destsize)
{
	size_t	i;
	size_t	j;
	char	*a;

	i = 0;
	j = ft_strlen(src);
	a = (char *)src;
	if (destsize == 0)
		return (j);
	while (a[i] != '\0' && i < (destsize - 1))
	{
		dest[i] = a[i];
		i++;
	}
	dest[i] = '\0';
	return (j);
}

// int	main(void)
// {
// 	char	dest[35];	
// 	char	src[] = "/home/amanjon/minishell_github/src/builtins";	

// 	printf("%zu\n", ft_strlcpy(dest, src, 35));
// 	printf("%s\n", dest);
// 	return (0);
// }
