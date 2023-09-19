/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_unsg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 07:24:29 by amanjon-          #+#    #+#             */
/*   Updated: 2023/05/12 07:34:10 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static int	ft_size_mem_unsg(unsigned long int n)
{
	int	i;

	i = 0;
	if (n == 0)
		i++;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_copy_in_mem_unsg(int k, char *ptr, unsigned long int n1)
{
	if (n1 == 0)
	{
		ptr[0] = '0';
		return (ptr);
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

char	*ft_itoa_unsg(unsigned int n)
{
	int					k;
	char				*ptr;
	unsigned long int	n1;

	n1 = n;
	k = ft_size_mem_unsg(n1);
	ptr = malloc(sizeof(char) * (k + 1));
	if (ptr == NULL)
		return (NULL);
	ptr[k] = '\0';
	return (ft_copy_in_mem_unsg(k, ptr, n1));
}

/* int main(void)
{
   
	printf("%s", ft_itoa_unsg(388));
	return(0);
	Para el unsigned "si es negativo" 4294967251 
} */
