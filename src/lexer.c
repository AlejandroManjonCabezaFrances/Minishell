/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 08:52:08 by amanjon-          #+#    #+#             */
/*   Updated: 2023/12/22 13:15:37 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_dsign(t_token **token_list, char *input, int i, char **env)
{
	t_token	*token;
	char	*varname;
	int		end;

	token = ms_lstnew();
	i++;
	end = i;
	while (input[end] && !is_space(input[end]) && !is_operator(input[end])
		&& !is_quote(input[end]) && !is_dsign(input[end]))
		end++;
	varname = ft_substr(input, i, end - i);
	token->content = find_var(varname, env);
	ms_lstadd_back(token_list, token);
	return (end);
}

int	handle_words(t_token **token_list, char *input, int i)
{
	t_token	*token;
	int		end;

	token = ms_lstnew();
	token->type = WORD;
	end = i;
	while (input[end] && !is_space(input[end]) && !is_operator(input[end])
		&& !is_quote(input[end]) && !is_dsign(input[end]))
		end++;
	token->content = ft_substr(input, i, end - i);
	ms_lstadd_back(token_list, token);
	return (end);
}

/**
 * This function save commands_tokens in list. '<' '<<' '>' '>>' '>&' '|' '/0'
 * @param	t_process *process, char *line, int i
 * @return	int
*/
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

int	handle_quotes(t_token **token_list, char *input, int i, char **env)
{
	t_token	*token;
	char	*str;
	int		end;
	int		quote;

	token = ms_lstnew();
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
	token->type = WORD;
	ms_lstadd_back(token_list, token);
	return (end);
}

/**
 * This function determines size of command_token find in the line commands (prompt)
 * @param	t_process *process, char *line
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