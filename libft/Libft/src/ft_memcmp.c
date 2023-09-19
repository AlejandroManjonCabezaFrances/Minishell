/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:17:33 by amanjon-          #+#    #+#             */
/*   Updated: 2023/05/12 07:31:44 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s11;
	unsigned char	*s22;
	size_t			i;

	s11 = (unsigned char *)s1;
	s22 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s11[i] != s22[i])
			return (s11[i] - s22[i]);
		i++;
	}
	return (0);
}

/*int main(void)
{
	char	s1[20] = "\xff\xaa\xde\xffMACOSX\xff";
	char	s2[20] = "\xff\xaa\xde\x02";

	printf("%d\n", memcmp(s1, s2, 8));
	printf("%d", ft_memcmp(s1, s2, 8));
	return (0);
}*/
