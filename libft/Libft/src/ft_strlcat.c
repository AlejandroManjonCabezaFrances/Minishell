/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 08:45:12 by amanjon-          #+#    #+#             */
/*   Updated: 2024/03/25 14:31:30 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
//retorna el tamaño completo de dst y src, y 
//solo concatena (si llega) el valor de dstsize.
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	k;

	k = ft_strlen(src);
	i = 0;
	while (dst[i] && i < dstsize)
		i++;
	j = 0;
	while (src[j] && ((i + j + 1) < dstsize))
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i < dstsize)
		dst[i + j] = '\0';
	return (i + k);
}

// int main(void)
// {
// 	// char	dst[35] = "hola ";
// 	// char	src[35] = "equipo";
// 	char	dst2[35] = "hola como va";
// 	char	src2[35] = "como";   
// 	// printf("%u\n", strlcat(dst, src, 4));
// 	// printf("%s \n",dst);
// 	printf("%lu\n", ft_strlcat(dst2, src2, 10));
// 	printf("%s \n",dst2);
// 	return(0);
// }
