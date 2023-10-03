/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:29:20 by amanjon-          #+#    #+#             */
/*   Updated: 2023/10/03 10:28:26 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_tokens(t_process *process, int i)
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
	return (1);
}

int ft_token_size(t_process *process)
{
	int i;
	int len;

	i = 0;
	len = 0;
	len = ft_strlen(&process->line[i]);
	while (process->line != NULL && process->line[i] && len != 0)
	{
		process->type_tokens = ft_tokens(process, i);
		if (process->type_tokens != 1)
		{
			printf("process.line[i] + i+1 = %c + %c\n", process->line[i], process->line[i+1]);
			printf("i = %d\n", i);
			return (i);
		}
		i++;
	}
	return (1);
}

int ft_save_token(t_process *process, t_node *node)
{
	t_node *temp;
	int i;

	i = 0;
	temp = ft_lstnew_mshell(NULL);
	i = ft_token_size(process);
	printf("i = %d\n", i);
	printf("process->type_tokens == %d\n", process->type_tokens);
	if (process->type_tokens == HEREDOC || process->type_tokens == APPEND)
		process->token = ft_substr(process->line, i, 2);
	else
		process->token = ft_substr(process->line, i, 1);
	node = ft_lstnew_mshell(process->token);
	ft_lstadd_back_mshell(&node, temp);
	while (node)
	{
		printf("temp = %s\n", node->content);
		node = node->next;
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	(void) argv;
	(void) env;
	t_process	process;
	t_node		node;
	int i;
	
	i = 0;
	if (argc != 1)
	{
		printf("enter only the executable ./minishell, thanks\n");
		return (1);
	}
	process.line = NULL;
	process.token = NULL;
	node.content = NULL;
	ft_signals();
	while (1)
	{
		process.line = readline("minishell-3.2$ ");
		if (process.line == NULL)
		{
			printf("function readline don `t open well\n");
			exit (0);
		}
		ft_save_token(&process, &node);
		printf("process.line = %s\n", process.line);
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