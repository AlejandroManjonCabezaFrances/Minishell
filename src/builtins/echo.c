/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:13:09 by amanjon-          #+#    #+#             */
/*   Updated: 2024/01/16 15:26:14 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	ft_echo(t_cmd *cmd)
// {
// 	int i;

// 	i = 0;
// 	while (cmd->command[i])
// 	{
// 		ft_putstr_fd(cmd->command[i], 1);		// stdout
// 		i++;
// 		if (cmd->command[i])
// 			write(1, " ", 1);
// 	}
// }