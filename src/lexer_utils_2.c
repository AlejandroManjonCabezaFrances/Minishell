/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 11:07:24 by marvin            #+#    #+#             */
/*   Updated: 2023/12/26 11:07:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*find_var(const char *varname, const char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(varname, env[i], ft_strlen(varname)) &&
			env[i][ft_strlen(varname)] == '=')
			return (env[i] + (ft_strlen(varname) + 1));
		i++;
	}
	return ("");
}

char	*quoted_dsign_all(const char *str, const char **env)
{
	char	*expanded;
	char	*varname;
	char	*var;
	int		start;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (is_dsign(str[i]))
		{
			i++;
			start = i;
			while (str[i] && !is_space(str[i]) && !is_operator(str[i])
				&& !is_quote(str[i]) && !is_dsign(str[i]))
				i++;
			varname = ft_substr(str, start, i - start);
			var = find_var(varname, env);
			if (var != NULL)
			{
				expanded = ft_strjoin(expanded, var);
				j += ft_strlen(var);
			}
		}
		else
		{
			expanded[j] = str[i];
			j++;
			i++;
		}
	}
	expanded[j] = '\0';
	return (expanded);
}