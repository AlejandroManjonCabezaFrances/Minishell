/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:29:20 by amanjon-          #+#    #+#             */
/*   Updated: 2023/10/13 18:19:19 by amanjon-         ###   ########.fr       */
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
 * This function find commands_tokens
 * @param	t_process *process, int i 
 * @return	int
*/
int ft_tokens_operators(t_process *process, int i)
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

//type_quptes = 0 --> no estamos dentro de comillas
//type_quptes = 1 --> dentro de comillas simples o dobles
void	ft_find_open_close_quotes(t_process *process, int *j, int *type_quotes)
{
	// while (process->line[*j] && ft_what_quotes(process->line[*j]) != (*type_quotes)) // Palabras sueltas y comillas opuestas
	// {
	// 	if (ft_what_quotes(process->line[*j] > 0))
	// 		(*type_quotes) = ft_what_quotes(process->line[*j]);
	// 	(*j)++;
	// }
	if (process->line[*j] && (*type_quotes) == 0 && ft_what_quotes(process->line[*j] > 0 ))  // dentro de mismas comillas
	{
		(*type_quotes) = ft_what_quotes(process->line[*j]);
		(*j)++;
		while (process->line[*j] && ft_what_quotes(process->line[*j] != (*type_quotes)))
			(*j)++;
		if (ft_what_quotes(process->line[*j]) == (*type_quotes))
			(*type_quotes) = 0; //fuera de las comillas
	}
}

int ft_tokens_words(t_process *process, int i)
{
	t_node	*temp;
	int 	j;
	int 	type_quotes;
	
	temp = ft_lstnew_mshell(NULL);
	j = i;
	type_quotes = ft_what_quotes(process->line[j]); // apertura posible comilla
	if(type_quotes)	// salta primera comilla
		j++;
	ft_find_open_close_quotes(process, &j, &type_quotes);
	while(process->line[j] && !ft_is_space(process->line[j]) && !ft_what_delimiter(process->line[j]))
		j++;
	temp->content = ft_substr(process->line, i, j - i);
	ft_lstadd_back_mshell(&process->tokens, temp);
	ft_print_lst(temp);
    return (j);
}

/**
 * This function save commands_tokens in list.
 * @param	t_process *process, t_node *node, int *i
 * @return	int
*/
void	ft_save_command_token(t_process *process, int *i)
{
	t_node *temp;
	
	temp = ft_lstnew_mshell(NULL);
	process->type_tokens = ft_tokens_operators(process, *i);
	if (process->type_tokens == HEREDOC || process->type_tokens == APPEND)
	{
		temp->content = ft_substr(process->line, *i, 2);
		*i = *i + 1;
	}
	else
		temp->content = ft_substr(process->line, *i, 1);
	ft_lstadd_back_mshell(&process->tokens, temp);
	ft_print_lst(temp);
}

/**
 * This function determines size of command_token find in the line commands (prompt)
 * @param	t_process *process
 * @return	int / 1.		int = size comand token / 1 = not find command token
*/
int ft_token_size(t_process *process)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(&process->line[i]);
	while (process->line != NULL && process->line[i] && len != 0)
	{
		if (ft_what_delimiter(process->line[i]))
			ft_save_command_token(process, &i);
		else
			ft_tokens_words(process, i);
		i++;
	}
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
		ft_token_size(&process);
		printf("process.line = %s\n", process.line);
		tcsetattr(0, 0, &g_info.termios);
	}
	free(process.line);
	return (0);
}

//######## getcwd();--> obtiene/muestra directorio dnde trabaja tu programa. Para el PWD######
// int main() 
// {
//     char cwd[1024]; // Búfer para almacenar la ruta
	
//     if (getcwd(cwd, sizeof(cwd)) != NULL) 
//         printf("Directorio de trabajo actual: %s\n", cwd); 
// 	else 
// 	{
//         perror("Error al obtener el directorio de trabajo actual\n");
//         return (1);
//     }
//     return (0);
// }