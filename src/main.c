/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:29:20 by amanjon-          #+#    #+#             */
/*   Updated: 2023/09/29 18:59:32 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void ft_hanger_sign(int sign)
{
	printf("\nSe recibió la señal SIGINT (Ctrl+C) con número %d. Saliendo...\n", sign);
	exit(0);
}

int ft_signal(void)
{
	// Registrar el manejador de señales para SIGINT
	signal(SIGINT, ft_hanger_sign);  // corto la señal con un exit();
	// signal(SIGINT, SIG_IGN);         // ignore, ignora el cortar la señal con ctrl;
	// signal(SIGINT, SIG_DFL);         // default, hace por defecto lo de bash
	printf("Presiona Ctrl+C para generar una señal SIGINT...\n");
	// Mantener el programa en ejecución
	while (1)
	{}
	return (0);
}


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
			printf("process.line[i] + i+1 = %c%c\n", process->line[i], process->line[i+1]);
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
	char *token;

	i = 0;
	temp = ft_lstnew_mshell(NULL);
	i = ft_token_size(process);
	printf("i = %d\n", i);
	printf("process->type_tokens == %d\n", process->type_tokens);
	if (process->type_tokens == HEREDOC || process->type_tokens == APPEND)
		token = ft_substr(process->line, i, 2);
	else
		token = ft_substr(process->line, i, 1);
	node = ft_lstnew_mshell(token);
	ft_lstadd_mshell(&node, temp);
	// while (tokens)
	// {
	// 	printf("temp -->%s\n", tokens->content);
	// 	tokens = tokens->next;
	// }
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
	while (1)
	{
		process.line = readline("minishell-3.2$ ");
		if (process.line == NULL)
		{
			printf("function readline don `t open well\n");
			exit (0);
		}
		/* i = ft_token_size(&process); */
		ft_save_token(&process, &node);
		/* printf("i = %d\n", i); */
		printf("process.line = %s\n", process.line);
	}
	ft_signal();
	free(process.line);
	return (0);
}

//###### readline();--> leer línea de comandos #######
// int	main(void)
// {
// 	char *input;
//     input = readline("Ingrese su nombre: ");
//     printf("Hola, %s!\n", input);
//     free(input);
// 	return (0);
// }

// ######## signal();--> para el (ctrl+c) ######

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