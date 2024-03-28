/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 20:25:53 by vini              #+#    #+#             */
/*   Updated: 2024/03/28 15:18:20 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*unquoted_str(char *unquoted, char *str, int i, int j)
{
	int		quote;

	while (str[i])
	{
		if (is_qte(str[i]))
		{
			quote = is_qte(str[i]);
			i++;
			while (quote != 0)
			{
				if (quote == is_qte(str[i]))
				{
					quote = 0;
					i++;
				}
				else
					unquoted[j++] = str[i++];
			}
		}
		else
			unquoted[j++] = str[i++];
	}
	unquoted[j] = '\0';
	return (unquoted);
}

int	count_flen(char *str, int i)
{
	int	f_len;
	int	quote;

	f_len = 0;
	quote = is_qte(str[i]);
	while (str[i++] && quote != 0)
	{
		if (quote == is_qte(str[i]))
			quote = 0;
		else
			f_len++;
	}
	return (f_len);
}

int	is_valid_char(char c)
{
	if ((!ft_isalnum(c) && (c != '_')) || (c == '?'))
		return (0);
	return (1);
}
