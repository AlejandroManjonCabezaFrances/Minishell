/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:58:37 by amanjon-          #+#    #+#             */
/*   Updated: 2023/09/29 11:40:28 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*a;
	size_t		i;

	if (ft_strlen(s) <= start)
		return (ft_strdup(""));
	if (ft_strlen(&s[start]) < len)
		len = ft_strlen(&s[start]);
	a = malloc(sizeof(char) * (len + 1));
	if (a == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start] != '\0')
	{
		a[i] = s[start];
		i++;
		start++;
	}
	a[i] = '\0';
	return (a);
}

/* int main(void)
{
	printf("%s\n", ft_substr("substring", 5, 3));
	
	return (0);
} */
/* Reserva(malloc(3)) y devuelve una substring de la string ’s’
substring empieza dsde l índice start y tiene una longitud máxima len
linea 22-23;ing->igualas l len = al tamaño q l queda dsps. del start */
