/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:09:21 by amanjon-          #+#    #+#             */
/*   Updated: 2023/06/22 09:23:50 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	ft_count_sub(char const *s, char c)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && j == 0)
		{
			j = 1;
			count++;
		}
		else if (s[i] == c)
		{
			j = 0;
		}
		i++;
	}
	return (count);
}

static int	ft_count_letters(char const *s, char c, int i)
{
	int	j;

	j = 0;
	while (s[i] != c && s[i])
	{
		j++;
		i++;
	}
	return (j);
}

static void	ft_free_subs(char **k, int subs)
{
	while (subs >= 0)
	{
		free (k[subs]);
		subs--;
	}
	free (k);
}

char	**ft_split(char const *s, char c)
{
	char	**k;
	int		subs;
	int		start;
	int		sub_len;

	start = 0;
	subs = -1;
	k = malloc(sizeof(char *) * (ft_count_sub(s, c) + 1));
	if (k == NULL)
		return (NULL);
	while (++subs < ft_count_sub(s, c))
	{
		while (s[start] == c)
			start++;
		sub_len = ft_count_letters(s, c, start);
		k[subs] = ft_substr(s, start, sub_len);
		if (k[subs] == NULL)
		{
			ft_free_subs(k, subs);
			return (NULL);
		}
		start = start + sub_len;
	}
	k[subs] = NULL;
	return (k);
}

/* int	main(void)
{
	char	s[] = "  hola  mundo  como estan todos  por aqui ";
	char	c = ' ';
	char	**k;
	int	i;

	i = 0;
	k = ft_split(s, c);
	while (k[i] != '\0')
	{
		printf("%s\n", k[i]);
		i++;
	}
	return (0);
} */
