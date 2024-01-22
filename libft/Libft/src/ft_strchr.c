/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 10:27:09 by amanjon-          #+#    #+#             */
/*   Updated: 2024/01/22 16:53:23 by marvin           ###   ########.fr       */
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

int	main(void)
{
	char s[] = "ALEX=hola";

	printf("Mi funcion %s\n", ft_strchr(s, '='));
	printf("Original %s", strchr(s, '='));
	return (0);
}
