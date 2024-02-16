/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_empty.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:54:07 by amanjon-          #+#    #+#             */
/*   Updated: 2024/02/16 13:19:24 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int main(int argc, char **argv, char **env)
// {
// 	(void) 	argc;
//     (void) 	argv;
// 	int i;

// 	i = 0;
// 	while (env[i])
// 	{
// 		printf("envi[%d] = %s\n", i, env[i]);
// 		i++;
// 	}
// 	if (env[i] == NULL)
// 		printf("env[i] == NULL\n");
// 	return (0);
// }

// gcc -Werror -Wextra -Wall env_empty.c -o prueba_env && ./prueba_env
// gcc -Werror -Wextra -Wall env_empty.c -o prueba_env && env -i ./prueba_env