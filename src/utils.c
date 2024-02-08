/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:44:58 by amanjon-          #+#    #+#             */
/*   Updated: 2024/01/30 07:55:27 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

/**
 * Create linked list of environment
 * @param	t_env **t_env, char **env
 * @return	void
*/
void ft_linked_list_env(t_env **envi, char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		ft_lstadd_back_str_env(envi, ft_lstnew_str_env(env[i]));
		i++;	
	}
}

void ft_print_lst_2(t_env *temp)
{
	while (temp)
	{
		printf("temp = %s\n", temp->content);
		temp = temp->next;
	}
}

void	dele(void *content)
{
	free(content);
}

void	ft_lstdelone_ms(t_env *lst, void (*del)(void *))
{
	if (lst != NULL && del != NULL)
	{
		(*del)(lst->content);
		free(lst);
	}
}

// ESTA EN LA LIBRERIA
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

// ESTA EN LA LIBRERIA
int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

// ESTA EN LA LIBRERIA
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

// ESTA EN LA LIBRERIA
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

// ESTA EN LA LIBRERIA
static void	ft_free_subs(char **k, int subs)
{
	while (subs >= 0)
	{
		free (k[subs]);
		subs--;
	}
	free (k);
}

// ESTA EN LA LIBRERIA
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

// ESTA EN LA LIBRERIA
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
