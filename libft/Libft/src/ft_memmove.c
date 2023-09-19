/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:04:23 by amanjon-          #+#    #+#             */
/*   Updated: 2023/05/12 07:31:52 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*a;
	char	*b;

	i = 0;
	a = (char *)src;
	b = (char *)dst;
	if (dst == src)
		return (dst);
	if (src < dst)
	{
		while (i < len--)
		{
			b[len] = a[len];
		}
	}
	else
	{
		while (i < len)
		{
			b[i] = a[i];
			i++;
		}
	}
	return (dst);
}

/* int main(void)
{
	char	dst[20];
	char	src[20] = "automovil";

	printf("%s\n", memmove(dst, src, 5));
	printf("%s", ft_memmove(dst, src, 5));

	return (0);
} */
