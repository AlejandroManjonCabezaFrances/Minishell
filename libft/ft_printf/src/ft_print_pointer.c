/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:30:00 by amanjon-          #+#    #+#             */
/*   Updated: 2023/05/12 07:21:36 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	ft_putpointer(unsigned long n)
{
	if (n >= 16)
	{
		ft_putpointer(n / 16);
		ft_putpointer(n % 16);
	}
	else
	{
		if (n <= 9)
			ft_putchar(n + '0');
		else
			ft_putchar(n - 10 + 'a');
	}
}

int	ft_pointer(unsigned long n)
{
	int	len;

	len = 0;
	len = len + write(1, "0x", 2);
	if (n == 0)
		len = len + write(1, "0", 1);
	else
	{
		ft_putpointer(n);
		len = len + ft_hexad_len(n);
	}
	return (len);
}
