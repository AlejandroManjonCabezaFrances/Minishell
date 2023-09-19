/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 10:27:09 by amanjon-          #+#    #+#             */
/*   Updated: 2023/05/12 07:32:29 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*a;

	a = (char *)s;
	i = 0;
	while (a[i] != '\0')
	{
		if (a[i] == (char)c)
			return (&a[i]);
	i++;
	}
	if (a[i] == (char)c)
		return (&a[i]);
	return (0);
}

/* int	main(void)
{
	char s[] = "automovil";

	printf("Mi funcion %s\n", ft_strchr(s, 'z'));
	printf("Original %s", strchr(s, 'z'));
	return (0);
} */
