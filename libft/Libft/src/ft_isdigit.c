/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:45:19 by amanjon-          #+#    #+#             */
/*   Updated: 2024/04/10 17:46:59 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_isdigit(int c)
{
	printf("c = %d\n", c);
	if (c >= 0 && c <= 9)
	{
		printf("entra en el if\n");
		return (1);
	}
	printf("NO ENTRA\n");
	return (0);
}

/*int	main(void)
{
	int	c;

	c = '1';
	printf("%d", ft_isdigit(c));
	return (0);
}*/
