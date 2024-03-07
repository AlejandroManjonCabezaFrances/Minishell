/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vini <vini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 22:03:54 by vini              #+#    #+#             */
/*   Updated: 2024/03/06 20:40:55 by vini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	closing_quote(char *str, int i)
{
	int	quote;

	quote = is_qte(str[i]);
	while (str[i++] && quote != 0)
		if (quote == is_qte(str[i]))
			quote = 0;
	return (i);
}

char	*quoted_dsign(char *str, char **env, int i)
{
	int	quote;

	quote = is_qte(str[i]);
	while (str[i++] && quote != 0)
	{
		if (quote == is_qte(str[i]))
			quote = 0;
		else if (str[i] == '$' && (ft_isalnum(str[i + 1])
				|| str[i + 1] == '?'))
			str = expand_dsign(str, env, 0);
	}
	return (str);
}

char	*expand(char *str, char **env)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (is_qte(str[i]))
		{
			quote = is_qte(str[i]);
			if (quote == DOUBLE_QUOTE)
				str = quoted_dsign(str, env, i);
			i = closing_quote(str, i);
		}
		else if (str[i] == '$' && str[i + 1])
			str = expand_dsign(str, env, 0);
		else
			i++;
	}
	return (str);
}

void	check_dsign(t_scmd *scmd, char **env)
{
	t_token	*aux;

	aux = scmd->wordlist;
	while (aux)
	{
		if (aux->type == WORD || aux->type == FILENAME)
			if (ft_strchr(aux->content, '$'))
				aux->content = expand(aux->content, env);
		aux = aux->next;
	}
	free(aux);
}

void	expand_var(t_scmd **scmds_list, char **env)
{
	t_scmd	*aux;

	aux = *scmds_list;
	while (aux)
	{
		check_dsign(aux, env);
		aux = aux->next;
	}
	free(aux);
}
