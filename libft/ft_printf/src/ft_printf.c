/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 09:47:11 by amanjon-          #+#    #+#             */
/*   Updated: 2023/08/02 13:01:25 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_operators(va_list args, int j, char *fmt)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	if (fmt[i] == 'c')
		x = ft_putchar_ft_printf(va_arg(args, int));
	else if (fmt[i] == 's')
		x = ft_putstr(va_arg(args, char *));
	else if (fmt[i] == 'i' || fmt[i] == 'd')
		x = ft_putstr_free(ft_itoa(va_arg(args, int)));
	else if (fmt[i] == 'u')
		x = ft_putstr_free(ft_itoa_unsg(va_arg(args, unsigned int)));
	else if (fmt[i] == 'x' || fmt[i] == 'X')
		x = ft_hexad(va_arg(args, unsigned int), *fmt);
	else if (fmt[i] == 'p')
		x = ft_pointer(va_arg(args, unsigned long));
	else if (fmt[i] == '%')
		x = ft_putchar_ft_printf('%');
	x = x + j;
	return (x);
}

int	ft_printf(char	const *fmt, ...)
{
	int		i;
	int		j;
	char	*str;
	va_list	args;

	i = 0;
	j = 0;
	str = (char *) fmt;
	va_start(args, fmt);
	while (str[i])
	{
		if (str[i] != '%')
			j = j + ft_putchar_ft_printf(str[i]);
		else if (str[i] == '%')
		{
			i++;
			j = ft_operators(args, j, &str[i]);
		}
		i++;
	}
	va_end(args);
	return (j);
}

/* int	main(void)
{	
	int ch1;
	int integer1;
	unsigned int unsg1;
	int num_decimal;
	int str1; 
	int hexad1;
	int pointer;
	void *ptr;
	int c;

	
	ch1 = 0;
	integer1 = 0;
	unsg1 = 0;
	num_decimal = 10345;
	ptr = (void *)51966;
	ptr = NULL; 
	c = 51966;
	c = -9;

	 ch1 = ft_printf("\n\nPrint a character: %c\n", 'a');
	printf("mi función %d\n", ch1);

	ch1 = printf("Print a character: %c\n", 'a');
	printf("función original %d\n\n", ch1);

	str1 = ft_printf("Print a string: %s\n", NULL);
	printf("mi funcion imprime: %d\n", str1);

	str1 = printf("Print a string: %s\n", NULL);
	printf("funcion original imprime: %d\n\n", str1); 


 	integer1 = ft_printf(" Print a integer: %d\n", -35544);
	printf("mi funcion: %d\n", integer1);

	integer1 = printf(" Print a integer: %d\n", -35544);
	printf("original %d\n\n", integer1); 

 	unsg1 = ft_printf("Print a unsigned %u\n", -82);
	printf("mi funcion %d\n", unsg1);

	unsg1 = printf("Print a unsigned %u\n", -82);
	printf("funcion original %d\n\n", unsg1);

	hexad1 = ft_printf("Print a hexadecimal %x\n", c);
	printf("mi funcion %d\n", hexad1);

	hexad1 = printf("Print a hexadecimal %x\n", c);
	printf("funcion original %d\n\n", hexad1);

	hexad1 = ft_printf("Print a hexadecimal %X\n", c);
	printf("mi funcion %d\n", hexad1);

	hexad1 = printf("Print a hexadecimal %X\n", c);
	printf("funcion original %d\n\n", hexad1);

	pointer = ft_printf("Print void * %p\n", ptr);
	printf("mi funcion %d\n", pointer);
	
	pointer = printf("Print void * %p\n", ptr);
	printf("funcion original %d\n\n", pointer); 

	return (0);
} */
