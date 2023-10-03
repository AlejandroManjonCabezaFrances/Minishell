/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:31:36 by amanjon-          #+#    #+#             */
/*   Updated: 2023/10/02 10:45:29 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
//funcion void se castea y se usa una variable puntero
void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*result;

	i = 0;
	result = (char *)b;
	while (i < len)
	{
		result[i] = c;
		i++;
	}
	return (result);
}

// int	main(void)
// {
//     char	b[15] = "ordenador";

// 	// printf("antes del memset: %s\n", b);
// 	// printf("%s\n", memset(b, 'a', sizeof(char) * 15));
// 	// printf("despues de memset; %s", b);
// 	//printf("%s", ft_memset(b, 'a', 10));
// 	return (0);
// }
