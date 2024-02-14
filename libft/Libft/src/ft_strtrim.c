/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 08:55:01 by amanjon-          #+#    #+#             */
/*   Updated: 2024/02/14 07:59:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	ft_start(char	const *s1, char	const *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (set[j])
	{
		if (s1[i] == set[j])
		{
			j = 0;
			i++;
		}
		else
			j++;
	}
	return (i);
}

static int	ft_end(char	const *s1, char	const *set)
{
	int	k;
	int	j;

	k = ft_strlen(s1);
	k--;
	j = 0;
	while (set[j])
	{
		if (s1[k] == set[j])
		{
			j = 0;
			k--;
		}
		else
			j++;
	}
	k++;
	return (k);
}

static char	*ft_fill(int i, int k, char	const *s1, char	*ptr)
{
	int	x;

	if (i > k)
		ptr = malloc(sizeof(char) * 1);
	else
		ptr = malloc(sizeof (char) * (k - i) + 1);
	if (ptr == NULL)
		return (NULL);
	x = 0;
	while (i < k)
	{
		ptr[x] = s1[i];
		x++;
		i++;
	}
	ptr[x] = '\0';
	return (ptr);
}

char	*ft_strtrim(char	const *s1, char	const *set)
{
	int		i;
	int		k;
	char	*ptr;

	ptr = NULL;
	if (s1[0] == '\0')
	{
		ptr = malloc(sizeof(char) * 1);
		if (!ptr)
		{
			free (ptr);
			return (0);
		}
		ptr[0] = '\0';
		return (ptr);
	}
	i = ft_start(s1, set);
	k = ft_end(s1, set);
	return (ft_fill(i, k, s1, ptr));
}

// int main(void)
// {
//     char    s1[] = "/home/amanjon/minishell_github/src/builtins";
//     char    set[] = "/builtins";

//     printf("%s", ft_strtrim(s1, set));
//     return(0);
// }