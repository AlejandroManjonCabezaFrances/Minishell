/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexad_x.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:03:00 by amanjon-          #+#    #+#             */
/*   Updated: 2023/05/12 07:21:02 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	ft_puthexad(unsigned long n, const char c)
{
	if (n >= 16)
	{
		ft_puthexad(n / 16, c);
		ft_puthexad(n % 16, c);
	}
	else
	{
		if (n <= 9)
			ft_putchar(n + '0');
		else
		{
			if (c == 'x')
				ft_putchar(n - 10 + 'a');
			else if (c == 'X')
				ft_putchar(n - 10 + 'A');
		}
	}
}

int	ft_hexad(unsigned long n, const char c)
{
	if (n == 0)
		return (write(1, "0", 1));
	else
		ft_puthexad(n, c);
	return (ft_hexad_len(n));
}
