/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:58:09 by amanjon-          #+#    #+#             */
/*   Updated: 2023/07/11 12:30:34 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*ptr;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	ptr = malloc(sizeof(char) * (ft_strlen_gnl_bonus((char *)s1)
				+ft_strlen_gnl_bonus((char *)s2)) + 1);
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
	free(s1);
	return (ptr);
}

size_t	ft_strlen_gnl_bonus(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strchrgnl_bonus(const char *s, int c)
{
	int		i;
	char	*a;

	a = (char *)s;
	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			return (&a[i + 1]);
		i++;
	}
	return (0);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t destsize)
{
	size_t	i;
	size_t	j;
	char	*a;

	i = 0;
	j = ft_strlen_gnl_bonus(src);
	a = (char *)src;
	if (destsize == 0)
		return (j);
	while (a[i] != '\0' && i < (destsize - 1))
	{
		dest[i] = a[i];
		i++;
	}
	dest[i] = '\0';
	return (j);
}
