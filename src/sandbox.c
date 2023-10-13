/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:20:52 by amanjon-          #+#    #+#             */
/*   Updated: 2023/10/13 17:49:24 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int	store_word(t_inf *info, char *line, int i)
// {
// 	int		j;
// 	int		type;
// 	char	*word;

// 	j = i;
// 	type = is_quote(line[j]);
// 	if (type)
// 		j++;
// 	store_word_aux(line, &j, &type);
// 	// if (line[j] && type > 0 && !is_space(line[j]))
// 	// 	type = 0 ;
// 	while (line[j] && !is_space(line[j]) && !is_delimiter(line[j]))
// 		j++;
// 	// if (type > 0) si estas dentro de comillas
// 	// 	j++;
// 	if (j > (int)ft_strlen(line))
// 		return (-1);
// 	word = ft_substr(line, i, j - i);
// 	ft_lstadd_back(&info->tokens, ft_lstnew(word));
// 	if (is_delimiter(line[j - 1]))
// 		return (j);
// 	return (j);
// }

// int ft_tokens_words(t_process *process, int i)
// {
//     int j;
//     int type;
//     /* char *word; */
// 	t_node *temp;

// 	type = 0;
// 	j = i;
// 	/* word = NULL; */
// 	temp = NULL;
// 	printf("antes de la funcion\n");
//     while (process->line[j])
//     {
//         if (ft_is_space(process->line[j]) || ft_what_delimiter(process->line[j]))
//         {
// 			printf("if 1/2\n");
//             if (type)	//type = 0, dentro de comillas
//             {
// 				printf("if 2/2\n");
//                 temp->content = ft_substr(process->line, i, j - i - 1);
//                 ft_lstadd_back_mshell(&process->tokens, ft_lstnew_mshell(temp->content));
//             }
//             return (j);
//         }
//         else if (!type)
//         {
// 			printf("if2\n");
//             i = j;
//             type = 1; // type = 1, fuera de comillas
//         }
//         else if (ft_what_quotes(process->line[j]) == type)
//         {
// 			printf("if 3\n");
//             temp->content = ft_substr(process->line, i + 1, j - i - 1);
//             ft_lstadd_back_mshell(&process->tokens, ft_lstnew_mshell(temp->content));
//             type = 0;
//         }
//         j++;
//     }
//     if (type)
//     {
// 		printf("if 4\n");
//         temp->content = ft_substr(process->line, i, j - i);
//         ft_lstadd_back_mshell(&process->tokens, ft_lstnew_mshell(temp->content));
//     }
// 	while (temp)
// 	{
// 		printf("temp = %s\n", temp->content);
// 		temp = temp->next;
// 	}
//     return (j);
// }


// void ft_open_close_different_quotes(char *line, int *j, int *type)
// {
//     char quote = line[(*j)]; // Almacenar el tipo de comilla actual

//     if (ft_is_quote(quote) > 0)
//     {
//         (*type) = ft_is_quote(quote); // Actualizar el tipo de comilla
//         (*j)++; // Avanzar al siguiente carácter

//         while (line[(*j)] && line[(*j)] != quote)
//         {
//             (*j)++; // Avanzar hasta encontrar el cierre de comilla
//         }

//         if (line[(*j)] == quote)
//         {
//             (*type) = 0; // Cerrar la comilla y restaurar el tipo a 0
//             (*j)++; // Avanzar al siguiente carácter después de la comilla cerrada
//         }
//     }
// }


// int	ft_store_word_aux(t_process *process, int i) 
// {
//     char quote;
// 	int flag;

// 	quote = 0;
//     while (process->line[i])
// 	{
//         if (/* (*type) == 0 &&  */(process->line[i] == '\'' || process->line[i] == '"'))
// 		{
//             quote = process->line[i];
// 			i++;
//             while (process->line[i] && process->line[i] != quote)
//                 i++;
//             if (process->line[i] == quote)
// 			{
//                 (flag) = 0;
//                 i++;
//             }
//         }
// 		else if ((flag) == 0 && !ft_is_space(process->line[i]) && !ft_what_delimiter(process->line[i]))
// 		{
//             (flag) = 1;
//             i++;
//         }
// 		else if ((flag) == 1 && (ft_is_space(process->line[i]) || ft_what_delimiter(process->line[i])))
// 		{
//             (flag) = 0;
//             i++;
//         }
// 		else
//             i++;
//     }
// 	return (i);
// }



/* ######################### ORIGINAL ######################### */
// static int ft_is_delimiter(const char *delimiters, char c)
// {
// 	while (*delimiters)
// 	{
// 		if (*delimiters == c)
// 			return (1);
// 		delimiters++;
// 	}
// 	return (0);
// }

// char *ft_strtok(char *restrict str, const char *restrict sep)
// {
// 	char		*tokenStart;
// 	static char	*nextToken;

// 	tokenStart = NULL;
// 	if (str != NULL)
// 		nextToken = str;
// 	while (*nextToken)
// 	{
// 		if (ft_is_delimiter(sep, *nextToken) == 0)
// 		{
// 			tokenStart = nextToken;
// 			while (*nextToken && ft_is_delimiter(sep, *nextToken) == 0)
// 				nextToken++;
// 			if (*nextToken)
// 			{
// 				*nextToken = '\0';
// 				nextToken++;
// 			}
// 			return (tokenStart);
// 		}
// 		nextToken++;
// 	}
// 	return (NULL);
// }

// int main()
// {
// 	char str[] = "hola \"que\" tal";
// 	const char sep[] = ",";
// 	char *token;
	
// 	token = ft_strtok(str, sep);
// 	while (token != NULL)
// 	{
// 		printf("token = %s\n", token);
// 		token = ft_strtok(NULL, sep);
// 	}
// 	return (0);
// }



/* ######################### VERSION LARGA ######################### */
// char *ft_strtok(char *restrict str, const char *restrict sep)
// {
//     static char *nextToken;
//     char *tokenStart;
//     char *delimiters;

//     tokenStart = NULL;
//     if (str != NULL)
//         nextToken = str;
//     while (*nextToken != '\0')
//     {
//         delimiters = (char *) sep;
//         while (*delimiters != '\0')
//         {
//             if (*nextToken == *delimiters)
//             {
//                 if (tokenStart != NULL)
//                 {
//                     *nextToken = '\0';
//                     nextToken++;
//                     return (tokenStart);
//                 }
//                 else
//                     nextToken++;
//             }
//             delimiters++;
//         }
//         if (tokenStart == NULL)
//             tokenStart = nextToken;
//         nextToken++;
//     }
//     if (tokenStart == NULL || *tokenStart == '\0')
//         return (NULL);
//     return (tokenStart);
// }
