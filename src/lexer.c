/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vini <vini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 12:11:27 by vipalaci          #+#    #+#             */
/*   Updated: 2024/03/06 20:17:40 by vini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_words(t_token **token_list, char *input, int i)
{
	t_token	*token;
	int		end;
	int		quote;

	end = i;
	quote = 0;
	while (input[end] && !is_space(input[end]) && !is_operator(input[end]))
	{
		if (is_qte(input[end]))
		{
			quote = is_qte(input[end]);
			while (input[end++] && quote != 0)
				if (quote == is_qte(input[end]))
					quote = 0;
			if (quote)
				return (-1);
		}
		else
			end++;
	}
	token = ms_lstnew();
	token->type = WORD;
	token->content = ft_substr(input, i, end - i);
	ms_lstadd_back(token_list, token);
	return (end);
}

int	handle_operators(t_token **token_list, char *input, int i)
{
	t_token	*token;

	token = ms_lstnew();
	token->type = operator_type(input, i);
	if (token->type == HEREDOC || token->type == APPEND)
	{
		token->content = ft_substr(input, i, 2);
		i++;
	}
	else
		token->content = ft_substr(input, i, 1);
	i++;
	ms_lstadd_back(token_list, token);
	return (i);
}

int	lexer(t_token **token_list, char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (is_space(input[i]))
			i++;
		else if (is_operator(input[i]))
			i = handle_operators(token_list, input, i);
		else
		{
			i = handle_words(token_list, input, i);
			if (i == -1)
				return (QUOTING_ERR);
		}
	}
	return (1);
}
