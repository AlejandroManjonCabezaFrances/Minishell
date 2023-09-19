/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 07:25:54 by amanjon-          #+#    #+#             */
/*   Updated: 2023/07/11 12:14:12 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <xlocale.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../../Libft/include/libft.h"

char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *s1, char *s2);
size_t	ft_strlen_gnl(const char *str);
char	*ft_strchr_gnl(const char *s, int c);
size_t	ft_strlcpy(char *dest, const char *src, size_t destsize);

#endif
