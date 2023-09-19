/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 08:10:23 by amanjon-          #+#    #+#             */
/*   Updated: 2023/05/12 07:33:05 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*ptr;

	i = 0;
	while (s[i] != '\0')
		i++;
	ptr = malloc((sizeof(char)) * i + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		ptr[i] = (*f)(i, s[i]);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

/*	char	(unsigned int i, char c)	  
{                                 
  	char	c;
if (c >= 'a' && c <= 'z')   
	c = c - 32;		     
if (c >= 'A' && c <= 'Z')
	c += 32;
return (c);
}
int main(void)
{
	char		str1[] = "abc ABC";	
	char*	str2;
	str2 = ft_strmapi(str1, *f);
	printf("%s\n", str2);
	return (0);
} */
