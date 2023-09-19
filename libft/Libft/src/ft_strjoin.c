/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 07:21:28 by amanjon-          #+#    #+#             */
/*   Updated: 2023/08/02 07:49:45 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		j;

	ptr = malloc(sizeof(char) * (ft_strlen((char *)s1)
				+ft_strlen((char *)s2)) + 1);
	i = 0;
	j = 0;
	if (ptr == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		ptr[j] = s1[i];
		j++;
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		ptr[j] = s2[i];
		j++;
		i++;
	}
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
