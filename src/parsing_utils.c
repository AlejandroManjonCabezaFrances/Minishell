/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:36:50 by amanjon-          #+#    #+#             */
/*   Updated: 2023/10/13 11:00:59 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_what_delimiter(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (TRUE);	
	return (FALSE);
}

int ft_what_quotes(char c)
{
	if (c == '\'')
		return (SINGLE_QUOTES);
	if (c == '"')
		return (DOUBLE_QUOTES);
	return (FALSE);
}

int ft_is_space(char c)
{
	if (c == ' ')
		return (TRUE);
	return (FALSE);
}