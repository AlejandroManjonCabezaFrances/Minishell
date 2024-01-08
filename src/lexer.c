/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 08:52:08 by amanjon-          #+#    #+#             */
/*   Updated: 2024/01/08 18:47:43 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * We save in a linked list the expansion of variables found in the prompt when
 * they are outside double quotes
 * @param	t_token **token_list, char *input, int i, char **env
 * @return	int
*/
int	handle_dsign(t_token **token_list, char *input, int i, char **env)
{
	t_token	*token;
	char	*varname;
	int		end;

	token = lstnew_ms();
	i++;
	end = i;
	while (input[end] && !is_space(input[end]) && !is_operator(input[end])
		&& !is_quote(input[end]) && !is_dsign(input[end]))
		end++;
	varname = ft_substr(input, i, end - i);
	token->content = find_var(varname, env);
	lstadd_back_ms(token_list, token);
	return (end);
}

/**
 * We save the words found in the promtp in a linked list.
 * @param	t_token **token_list, char *input, int i
 * @return	int
*/
int	handle_words(t_token **token_list, char *input, int i)
{
	t_token	*token;
	int		end;

	token = lstnew_ms();
	token->type = WORD;
	end = i;
	while (input[end] && !is_space(input[end]) && !is_operator(input[end])
		&& !is_quote(input[end]) && !is_dsign(input[end]))
		end++;
	token->content = ft_substr(input, i, end - i);
	lstadd_back_ms(token_list, token);
	return (end);
}

/**
 * We save the different operators found in the prompt in a linked list.
 *  '<' '<<' '>' '>>' '|'
 * @param	t_token **token_list, char *input, int i
 * @return	int
*/
int	handle_operators(t_token **token_list, char *input, int i)
{
	t_token	*token;

	token = lstnew_ms();
	token->type = operator_type(input, i);
	if (token->type == HEREDOC || token->type == APPEND)
	{
		token->content = ft_substr(input, i, 2);
		i++;
	}
	else
		token->content = ft_substr(input, i, 1);
	i++;
	lstadd_back_ms(token_list, token);
	return (i);
}

/**
 * We control what type of quotes are in the promt and tokenize what is in
 * inside it, saving it in a linked list. We also control the expansion of variables
 * when enclosed in double quotes
 * @param	t_token **token_list, char *input, int i, char **env
 * @return	int
*/
int	handle_quotes(t_token **token_list, char *input, int i, char **env)
{
	t_token	*token;								
	char	*str;
	int		end;
	int		quote;

	token = lstnew_ms();
	quote = is_quote(input[i]);
	end = i;
	while (input[end++] && quote != 0)
		if (quote == is_quote(input[end]))
			quote = 0;
	if (quote)
		return (QUOTING_ERR);
	str = ft_substr(input, i, end - i);
	if (is_quote(input[i]) == SINGLE_QUOTE)
		token->content = str;
	else if (is_quote(input[i]) == DOUBLE_QUOTE)
		token->content = quoted_dsign(str, env);
	token->type = QUOTED_WORD;
	lstadd_back_ms(token_list, token);
	return (end);
}

/**
 * This function determines what is in the prompt: spaces, quotes, operators
 * or variable expansion
 * @param	t_token **token_list, char *input, char **env
 * @return	int
*/
int	lexer(t_token **token_list, char *input, char **env)
{
	int	i;

	i = 0;
	while (input && input[i])
	{
		if (is_space(input[i]))
			i++;
		else if (is_quote(input[i]))
		{
			i = handle_quotes(token_list, input, i, env);
			if (i == QUOTING_ERR)
				return (i);
		}
		else if (is_operator(input[i]))
			i = handle_operators(token_list, input, i);
		else if (is_dsign(input[i]))
			i = handle_dsign(token_list, input, i, env);
		else
			i = handle_words(token_list, input, i);
	}
	return (1);
}