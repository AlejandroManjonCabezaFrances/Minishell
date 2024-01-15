/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:20:52 by amanjon-          #+#    #+#             */
/*   Updated: 2024/01/15 13:01:13 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Obtener el PWD --> Current working directory
*/
int main()
{
	char cwd[1024];

	cwd[0] = '\0';
	if (getcwd(cwd, sizeof(cwd)) != NULL/*  && cwd[0] != '\0' */)
		printf("directorio trabajo actual = %s\n", cwd);
	else
	{
		perror(cwd);
		return (-1);
	}	
	return (0);
}

// ######## getcwd();--> obtiene/muestra directorio dnde trabaja tu programa. Para el PWD######
int main() 
{
    char cwd[1024]; // Búfer para almacenar la ruta
	
    if (getcwd(cwd, sizeof(cwd)) != NULL) 
        printf("Directorio de trabajo actual: %s\n", cwd); 
	else 
	{
        perror("Error al obtener el directorio de trabajo actual\n");
        return (1);
    }
    return (0);
}

char *ft_strtok(char *restrict str, const char *restrict sep)
{
	char		*tokenStart;
	static char	*nextToken;

	tokenStart = NULL;
	if (str != NULL)
		nextToken = str;
	while (*nextToken)
	{
		if (ft_is_delimiter(sep, *nextToken) == 0)
		{
			tokenStart = nextToken;
			while (*nextToken && ft_is_delimiter(sep, *nextToken) == 0)
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
	char str[] = "hola \"que\" tal";
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



/* ######################### VERSION LARGA ######################### */
char *ft_strtok(char *restrict str, const char *restrict sep)
{
    static char *nextToken;
    char *tokenStart;
    char *delimiters;

    tokenStart = NULL;
    if (str != NULL)
        nextToken = str;
    while (*nextToken != '\0')
    {
        delimiters = (char *) sep;
        while (*delimiters != '\0')
        {
            if (*nextToken == *delimiters)
            {
                if (tokenStart != NULL)
                {
                    *nextToken = '\0';
                    nextToken++;
                    return (tokenStart);
                }
                else
                    nextToken++;
            }
            delimiters++;
        }
        if (tokenStart == NULL)
            tokenStart = nextToken;
        nextToken++;
    }
    if (tokenStart == NULL || *tokenStart == '\0')
        return (NULL);
    return (tokenStart);
}
