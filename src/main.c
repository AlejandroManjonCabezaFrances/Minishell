/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:29:20 by amanjon-          #+#    #+#             */
/*   Updated: 2023/10/19 15:42:16 by amanjon-         ###   ########.fr       */
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
 * @param	t_process *process, int i 
 * @return	int
*/
int ft_tokens_delimiters(t_process *process, int i)
{  
		if (process->line[i] == '>' && process->line[i + 1] == '>')
			return (APPEND);
		else if (process->line[i] == '<' && process->line[i + 1] == '<')
			return (HEREDOC);
		else if (process->line[i] == '>')
			return (GREAT);
		else if (process->line[i] == '<')
			return (LESS);
		else if (process->line[i] == '>' && process->line[i + 1] == '&')
			return (GREATAMPERSAND);
		else if (process->line[i] == '|')
			return (PIPE);
		else if (process->line[i] == '\0')
			return (END);
	return (FALSE);
}

/**
 * This function (iterates when we are inside or outside quotes) and (handles both opening and closing of quotes and how we switch between these states)
 * @param	t_process *process, int *j, int *type_quotes 
 * @return	void
*/
void	ft_find_open_close_quotes(t_process *process, int *j, int *quote)
{
	while (process->line[*j] && ft_what_quotes(process->line[*j]) != (*quote) && (*quote) > 0)
		(*j)++;
}

/**
 * This function tokenizes words inside/outside quotes, type_quotes = 0 inside, type_quotes = !0 outside
 * @param	t_process *process, int i
 * @return	int
*/
int ft_save_tokens_words(t_process *process, int i)
{
	t_process	*temp;
	int 		j;
	int 		quote;
	
	temp = ft_lstnew_mshell(NULL);
	j = i;
	quote = ft_what_quotes(process->line[j]); // 0 --> fuera de comillas    1 --> dentro de comillas
	if(quote != 0)	// salta primera comilla
		j++;
	ft_find_open_close_quotes(process, &j, &quote);
	if (process->line[j] && quote > 0 && !ft_is_space(process->line[j])) // cuando sales de comillas actualizas quote
		quote = 0;
	while (process->line[j] && !ft_is_space(process->line[j]) && !ft_what_delimiter(process->line[j]))  // itere la comilla cierre
		j++;
	/* if (quote > 0)
		j++; */
	temp->content = ft_substr(process->line, i, j - i);
	ft_lstadd_back_mshell(&process, temp);
	free(temp);
    return (j);
}

/**
 * This function save commands_tokens in list. '<' '<<' '>' '>>' '>&' '|' '/0'
 * @param	t_process *process, t_node *node, int *i
 * @return	int
*/
void	ft_save_tokens_delimiters(t_process *process, int i)
{
	t_process *temp;
	
	temp = ft_lstnew_mshell(NULL);
	process->type_tokens = ft_tokens_delimiters(process, i);
	if (process->type_tokens == HEREDOC || process->type_tokens == APPEND)
	{
		temp->content = ft_substr(process->line, i, 2);
		i++;
	}
	else
		temp->content = ft_substr(process->line, i, 1);
	i++;
	ft_lstadd_back_mshell(&process, temp);
	free(temp);
}

/**
 * This function determines size of command_token find in the line commands (prompt)
 * @param	t_process *process
 * @return	int / 1.		int = size comand token / 1 = not find command token
*/
int ft_tokenize(t_process *process)
{
	int i;

	i = 0;
	while (process->line != NULL && process->line[i])
	{
		if (ft_is_space(process->line[i]))
			i++;
		else if (ft_what_delimiter(process->line[i]))
			ft_save_tokens_delimiters(process, i);
		else
			i = ft_save_tokens_words(process, i);
		i++;
	}
	ft_print_lst(process);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	(void) argv;
	(void) env;
	t_process	process;
	/* t_node		node; */
	int i;
	
	process.line = NULL;
	/* node.content */
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
		process.line = readline("minishell-3.2$ ");
		if (process.line == NULL)
		{
			printf("function readline don `t open well\n");
			exit (0);
		}
		ft_tokenize(&process);
		printf("process.line = %s\n", process.line);
		tcsetattr(0, 0, &g_info.termios);
	}
	free(process.line);
	return (0);
}
