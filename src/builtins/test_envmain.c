/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_envmain.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 09:49:08 by amanjon-          #+#    #+#             */
/*   Updated: 2024/02/16 09:55:54 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int main(int argc, char **argv, char **env)
{
	(void) 	argc;
    (void) 	argv;
	
	unsigned int i;

	i = 0;
	while (env[i])
	{
		printf("envi[%u] = %s\n", i, env[i]);
		i++;
	}
	return (0);
}

// gcc -Wall -Werror -Wextra test_envmain.c -o exec_test_envmain && ./exec_test_envmain && rm exec_test_envmain
// gcc -Wall -Werror -Wextra test_envmain.c -o exec_test_envmain && env -i ./exec_test_envmain && rm exec_test_envmain