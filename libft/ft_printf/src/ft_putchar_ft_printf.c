/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_ft_printf.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:44:42 by amanjon-          #+#    #+#             */
/*   Updated: 2023/08/02 12:50:20 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_putchar_ft_printf(char c)
{
	write(1, &c, 1);
	return (1);
}

/* int main(void)
{
	char	c;

	c = 'a';
	ft_putchar(c);
	return (0);
} */