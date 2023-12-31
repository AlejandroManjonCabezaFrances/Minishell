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

/**
 * Compares the possible environment variable found with the environment variables
 * and returns a pointer to the start of the value of the environment variable found. Ex: USER
 * If not, returns an empty string
 * @param	char *varname, char **env
 * @return	char
*/
char	*find_var(char *varname, char **env)
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

/**
 * Receives expansion of variable, indexes and the environment.
 * This function replaces the found environment variable with its value
 * correspondent
 * @param	char *source, int start, int end, char **env
 * @return	char
*/
char	*expand(char *source, int start, int end, char **env)
{
	char	*expand;
	char	*varname;
	char	*var;
	int		i;
	int		j;
	
	varname = ft_substr(source, start, end - start);
	var = find_var(varname, env);
	free (varname);
	expand = malloc(sizeof(char) * (ft_strlen(source) + ft_strlen(var) + 1));
	if (expand == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (j < start - 1)
	{
		expand[j] = source[j];
		j++;
	}
	while (var[i])
		expand[j++] = var[i++];
	while (source[end])
		expand[j++] = source[end++];
	expand[j] = '\0';
	return (expand);
}

/**
 * It 's goal is to find and expand environment variables preceded by the dollar
 * sign ($) in str.
 * Returns the content of the expanded variable
 * @param	char *str, char **env
 * @return	char
*/
char	*quoted_dsign(char *str, char **env)
{
	char	*expanded;
	char	*temp;
	int		start;
	int		end;

	expanded = ft_strdup(str);
	start = 0;
	while (expanded[start])
	{
		if (is_dsign(expanded[start]))
		{
			start++;
			end = start;
			while (expanded[end] && !is_space(expanded[end]) && !is_operator(expanded[end])
				&& !is_quote(expanded[end]) && !is_dsign(expanded[end]))
				end++;
			temp = expand(expanded, start, end, env);
			free(expanded);
			expanded = temp;
			start--;
		}
		else
			start++;
	}
	return (expanded);
}
