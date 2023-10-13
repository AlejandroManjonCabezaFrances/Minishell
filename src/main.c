/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:29:20 by amanjon-          #+#    #+#             */
/*   Updated: 2023/10/13 11:10:54 by amanjon-         ###   ########.fr       */
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

// /**
//  * This function find open/close quotes and rest of prompt.
//  * @param	t_process *process, int i 
//  * @return	int, size of prompt ?¿?¿?¿
// */
// int	ft_token_word_aux(t_process *process, int i) 
// {
//     char	quote;
// 	int		j;
// 	char	*word;
// 	int		flag;
// 	t_node *temp;
	
 
// 	quote = 0;
// 	j = i;
// 	flag = 0;
// 	temp = NULL;
//     while (process->line[j])
// 	{
//         if (process->line[j] == '\'' || (process->line[j] == '"' && j == i))
// 		{
//             quote = process->line[j];	// inicia comillas
// 			j++;
// 		}
//         else if (process->line[j] == quote)		// NO ENTRA AQUI   #########################################################################
// 		{
// 			quote = 0;					//	finaliza comillas
// 			word = ft_substr(process->line, i, j - i);
// 			temp = ft_lstnew_mshell(word);
// 			ft_lstadd_back_mshell(&node, temp);
// 			j++;
// 		}
// 		else
//             j++;
// 		while (node)
// 		{
// 			printf("temp = %s\n", node->content);
// 			node = node->next;
// 		}
// 		// else if ((flag) == 0 && !ft_is_space(process->line[i]) && !ft_what_delimiter(process->line[i]))
// 		// {
//         //     flag = 1;					//	empieza palabra
//         //     i++;
//         // }
// 		// else if ((flag) == 1 && (ft_is_space(process->line[i]) || ft_what_delimiter(process->line[i])))
// 		// {
//         //     flag = 0;					//	finaliza palabra
//         //     i++;
//         // }
//     }
// 	return (0);
// }

// int	ft_tokens_words(t_process *process, int i)
// {
// 	process->type_quotes = ft_what_quotes(process->line[i]);
// 	ft_token_word_aux(process, i);
	
// 	return (0);
// }




int ft_tokens_words(t_process *process, int i)
{
    int j;
    int type;
    /* char *word; */
	t_node *temp;

	type = 0;
	j = i;
	/* word = NULL; */
	temp = NULL;
	printf("antes de la funcion\n");
    while (process->line[j])
    {
        if (ft_is_space(process->line[j]) || ft_what_delimiter(process->line[j]))
        {
			printf("if 1/2\n");
            if (type)
            {
				printf("if 2/2\n");
                temp->content = ft_substr(process->line, i, j);
                ft_lstadd_back_mshell(&process->tokens, ft_lstnew_mshell(temp->content));
            }
            return (j);
        }
        else if (!type)
        {
			printf("if2\n");
            i = j;
            type = 1;
        }
        else if (ft_what_quotes(process->line[j]) == type)
        {
			printf("if 3\n");
            temp->content = ft_substr(process->line, i + 1, j - i - 1);
            ft_lstadd_back_mshell(&process->tokens, ft_lstnew_mshell(temp->content));
            type = 0;
        }
        j++;
    }
    if (type)
    {
		printf("if 4\n");
        // temp->content = ft_substr(process->line, i, j - i);
        // ft_lstadd_back_mshell(&process->tokens, ft_lstnew_mshell(temp->content));
    }
	while (temp)
	{
		printf("temp = %s\n", temp->content);
		temp = temp->next;
	}
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
	while (temp)
	{
		printf("temp = %s\n", temp->content);
		temp = temp->next;
	}
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