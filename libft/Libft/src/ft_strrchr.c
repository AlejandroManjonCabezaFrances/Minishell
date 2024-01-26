/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:16:17 by amanjon-          #+#    #+#             */
/*   Updated: 2024/01/25 11:22:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*a;

	a = (char *)s;
	i = ft_strlen(a);
	if (c == '\0')
		return (&a[i]);
	while (i >= 0)
	{
		if (a[i] == (char)c)
			return (&a[i]);
	i--;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char	s[] = "ALEX=hola";

// 	printf("original %s\n", strrchr(s, '=')); 
// 	printf("mia %s", ft_strrchr(s, '=')); 
// 	return (0);
// }
