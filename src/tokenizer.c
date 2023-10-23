/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 08:52:08 by amanjon-          #+#    #+#             */
/*   Updated: 2023/10/23 08:53:22 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * This function find tokens_delimiters
 * @param	char *line, int i 
 * @return	int
*/
int ft_tokens_delimiters(char *line, int i)
{  
		if (line[i] == '>' && line[i + 1] == '>')
			return (APPEND);
		else if (line[i] == '<' && line[i + 1] == '<')
			return (HEREDOC);
		else if (line[i] == '>')
			return (GREAT);
		else if (line[i] == '<')
			return (LESS);
		else if (line[i] == '>' && line[i + 1] == '&')
			return (GREATAMPERSAND);
		else if (line[i] == '|')
			return (PIPE);
		else if (line[i] == '\0')
			return (END);
	return (FALSE);
}

/**
 * This function (iterates when we are inside or outside quotes) and (handles both opening and closing of quotes and how we switch between these states)
 * @param	char *line, int *j, int *quote 
 * @return	void
*/
void	ft_find_open_close_quotes(char *line, int *j, int *quote)
{
	while (line[*j] && ft_what_quotes(line[*j]) != (*quote) && (*quote) > 0)
		(*j)++;
}

/**
 * This function tokenizes words inside/outside quotes, type_quotes = 0 inside, type_quotes = !0 outside
 * @param	t_process *process, char *line, int i
 * @return	int
*/
int ft_save_tokens_words(t_process **process, char *line, int i)
{
	t_process	*temp;
	int 		j;
	int 		quote;
	
	temp = ft_lstnew_mshell();
	j = i;
	quote = ft_what_quotes(line[j]); // 0 --> fuera de comillas    1 --> dentro de comillas
	if(quote != 0)	// salta primera comilla
		j++;
	ft_find_open_close_quotes(line, &j, &quote);
	if (line[j] && quote > 0 && !ft_is_space(line[j])) // cuando sales de comillas actualizas quote
		quote = 0;
	while (line[j] && !ft_is_space(line[j]) && !ft_what_delimiter(line[j]))  // itere la comilla cierre
		j++;
	/* if (quote > 0)
		j++; */
	temp->content = ft_substr(line, i, j - i);
	ft_lstadd_back_mshell(process, temp);
	free(temp);
    return (j);
}

/**
 * This function save commands_tokens in list. '<' '<<' '>' '>>' '>&' '|' '/0'
 * @param	t_process *process, char *line, int i
 * @return	int
*/
int	ft_save_tokens_delimiters(t_process **process, char *line, int i)
{
	t_process *temp;
	
	temp = NULL;
	temp = ft_lstnew_mshell();
	temp->type_tokens = ft_tokens_delimiters(line, i);
	if (temp->type_tokens == HEREDOC || temp->type_tokens == APPEND)
	{
		temp->content = ft_substr(line, i, 2);
		i++;
	}
	else
		temp->content = ft_substr(line, i, 1);
	i++;
	ft_lstadd_back_mshell(process, temp);
	free(temp);
	return (i);
}

/**
 * This function determines size of command_token find in the line commands (prompt)
 * @param	t_process *process, char *line
 * @return	int
*/
int ft_tokenize(t_process **process, char *line)
{
	int i;

	i = 0;
	while (line && line[i])
	{
		if (ft_is_space(line[i]))
			i++;
		else if (ft_what_delimiter(line[i]))
			i = ft_save_tokens_delimiters(process, line, i);
		else
			i = ft_save_tokens_words(process, line, i);
		i++;
	}
	ft_print_lst(*process);
	return (0);
}