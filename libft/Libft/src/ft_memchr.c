/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:45:45 by amanjon-          #+#    #+#             */
/*   Updated: 2023/12/27 12:44:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*a;
	unsigned char	cu;
	size_t			i;

	cu = (unsigned char)c;
	a = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (a[i] == cu)
			return (&a[i]);
		i++;
	}
	return (0);
}

/*int main(void)
{
	char	s[] = "autocarvana";

	printf("%s\n", memchr(s, '\0', 11));
	printf("%s\n", ft_memchr(s, '\0', 11));
	return (0);
}*/
