/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:27:38 by amanjon-          #+#    #+#             */
/*   Updated: 2023/12/26 14:27:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <string.h>
# include <unistd.h>
// # include <xlocale.h>
# include <stdlib.h>
# include "../../Libft/include/libft.h"

int		ft_printf(char const *fmt, ...);
int		ft_operators(va_list args, int j, char *fmt);
int		ft_putstr(char *str);
int		ft_putchar_ft_printf(char c);
char	*ft_itoa(int n);
char	*ft_itoa_unsg(unsigned int n);
int		ft_hexad_len(unsigned long n);
void	ft_putpointer(unsigned long n);
int		ft_pointer(unsigned long n);
void	ft_puthexad(unsigned long n, const char c);
int		ft_hexad(unsigned long n, const char c);
int		ft_putstr_free(char *str);

#endif
