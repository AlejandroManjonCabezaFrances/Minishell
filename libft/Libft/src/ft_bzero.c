/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 07:58:29 by amanjon-          #+#    #+#             */
/*   Updated: 2023/05/12 07:23:26 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
//s = La dirección inicial en el área de bytes.
//n = El tamaño de los datos.
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;
	size_t			i;

	i = 0;
	str = (unsigned char *) s;
	if (n == 0)
		return ;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}

/*int main(void)
{
	const char s[20] = "hola";
    
	ft_bzero(*s, 2);
	return (0);
}*/
