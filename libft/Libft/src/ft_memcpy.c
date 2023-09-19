/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 09:26:30 by amanjon-          #+#    #+#             */
/*   Updated: 2023/05/12 07:31:48 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dst1;
	char	*src1;

	dst1 = (char *)dst;
	src1 = (char *)src;
	i = 0;
	if ((dst1 == NULL && src1 == NULL))
		return (0);
	while (i < n)
	{
		dst1[i] = src1[i];
		i++;
	}
	return (dst1);
}

/* int	main(void)
{
	char	dst[20];
	char	src[20] = "hola que tal";
	printf("%s\n", memcpy(dst, src, 3));
	printf("%s", ft_memcpy(dst, src, 3));
	return (0);
} */
