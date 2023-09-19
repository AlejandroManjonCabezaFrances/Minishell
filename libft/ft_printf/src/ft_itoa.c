/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 07:49:45 by amanjon-          #+#    #+#             */
/*   Updated: 2023/05/12 07:20:57 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static int	ft_size_mem(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		i++;
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_copy_in_mem(int k, char	*ptr, long n1)
{
	if (n1 == 0)
	{
		ptr[0] = '0';
		return (ptr);
	}
	if (n1 < 0)
	{
		ptr[0] = '-';
		n1 = n1 * (-1);
	}
	k--;
	while (k >= 0 && n1 != 0)
	{
		ptr[k] = n1 % 10 + '0';
		n1 = n1 / 10;
		k--;
	}
	return (ptr);
}

char	*ft_itoa(int n)
{
	int		k;
	char	*ptr;
	long	n1;

	n1 = n;
	k = ft_size_mem(n1);
	ptr = malloc(sizeof(char) * (k + 1));
	if (ptr == NULL)
		return (NULL);
	ptr[k] = '\0';
	return (ft_copy_in_mem(k, ptr, n1));
}

/* int main(void)
{
   
	printf("%s", ft_itoa(-388));
	return(0);
} */