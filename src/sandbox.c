/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:20:52 by amanjon-          #+#    #+#             */
/*   Updated: 2023/10/05 17:23:38 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

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

static int ft_is_delimiter(const char *delimiters, char c)
{
	while (*delimiters)
	{
		if (*delimiters == c)
			return (1);
		delimiters++;
	}
	return (0);
}

char *ft_strtok(char *restrict str, const char *restrict sep)
{
	char		*tokenStart;
	static char	*nextToken;

	if (str != NULL)
		nextToken = str;

	while (*nextToken)
	{
		if (!ft_is_delimiter(sep, *nextToken))
		{
			tokenStart = nextToken;
			while (*nextToken && !ft_is_delimiter(sep, *nextToken))
				nextToken++;
			if (*nextToken)
			{
				*nextToken = '\0';
				nextToken++;
			}
			return (tokenStart);
		}
		nextToken++;
	}
	return (NULL);
}

int main()
{
	char str[] = "Hola,Mundo,Esta,Es,Una,Prueba";
	const char sep[] = ",";
	char *token;
	
	token = ft_strtok(str, sep);
	while (token != NULL)
	{
		printf("token = %s\n", token);
		token = ft_strtok(NULL, sep);
	}
	return (0);
}

// int main()
// {
//     char str[] = "'\0";
//     const char sep[] = ",";
//     char *token;
	
//     token = strtok(str, sep);
//     while (token != NULL)
//     {
//         printf("token = %s\n", token);
//         token = strtok(NULL, sep);
//     }
//     return (0);
// }