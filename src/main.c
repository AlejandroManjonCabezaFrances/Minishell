/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:29:20 by amanjon-          #+#    #+#             */
/*   Updated: 2023/10/20 17:05:46 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * This function disable chars printed by ctrl+c '^C'
 * @param	void
 * @return	void
*/
static void	ft_disable_ctrl_c_printing_chars(void)
{
	int rc;

	rc = tcgetattr(0, &g_info.termios);
	if (rc != 0)
	{
		perror("tcgetattr");
		exit (1);
	}
	g_info.termios.c_lflag &= ~ECHOCTL;
	rc = tcsetattr(0, 0, &g_info.termios);
	if (rc != 0)
	{
		perror("tcsetattr");
		exit(1);
	}
}

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
	while (line != NULL && line[i])
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

int	main(int argc, char **argv, char **env)
{
	t_process	*process;
	char *line;
	int i;
	(void) argv;
	(void) env;
	
	process = NULL;
	line = NULL;
	i = 0;
	ft_disable_ctrl_c_printing_chars();
	if (argc != 1)
	{
		printf("enter only the executable ./minishell, thanks\n");
		return (1);
	}
	while (1)
	{
		ft_signals();
		line = readline("minishell-3.2$ ");
		if (line == NULL)
		{
			printf("function readline don `t open well\n");
			exit (0);
		}
		ft_tokenize(&process, line);
		printf("line = %s\n", line);
		tcsetattr(0, 0, &g_info.termios);
	}
	free(line);
	return (0);
}
