/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 07:21:28 by amanjon-          #+#    #+#             */
/*   Updated: 2024/04/11 10:00:41 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	ptr = malloc(sizeof(char) * (ft_strlen((char *)s1)
				+ft_strlen((char *)s2)) + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
		ptr[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		ptr[j++] = s2[i++];
	ptr[j] = '\0';
	return (ptr);
}

/* int main(void)
{
	char	s1[] = "hola ";
	char	s2[] = "caracola";

	printf("%s", ft_strjoin(s1, s2));
    return(0);
} */
