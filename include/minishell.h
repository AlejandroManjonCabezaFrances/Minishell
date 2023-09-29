/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:29:49 by amanjon-          #+#    #+#             */
/*   Updated: 2023/09/29 18:59:51 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* --- LIBRARIES --- */
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h> 
# include <sys/stat.h>
# include <errno.h>

/* ---------- NEW ---------- */
#include <readline/readline.h>	//funcion readline -prompt-
#include <signal.h> 			//funcion signal

/* ---------------- PATH ---------------- */
# include "../libft/Libft/include/libft.h"
# include "../libft/ft_printf/include/ft_printf.h"
# include "../libft/Gnl/include/get_next_line.h"

/* ------ STRUCT ------ */
typedef struct s_process
{
	char *line;
	int type_tokens;	// < << > >> | >& \0
}	t_process;

typedef struct s_node
{
	char			*content;
	struct s_node	*next;
}	t_node;

/* ------ MACROS ------ */
#define GREAT			3	//'>'
#define	LESS			4	//'<'
#define	APPEND			5	//'>>'
#define	HEREDOC			6	//'<<'
#define	GREATAMPERSAND	7	//'>&'
#define	PIPE			8	//'|'
#define	END				9	//'\0'

/* ----------------- FUNCTION ----------------- */
int		main(int argc, char **argv, char **env);
int		ft_tokens(t_process *process, int i);
int		ft_signal(void);
void	ft_hanger_sign(int sign);
int		ft_save_token(t_process *process, t_node *node);
t_node	*ft_lstnew_mshell(char *content);
int		ft_token_size(t_process *process);
void	ft_lstadd_mshell(t_node **lst, t_node *new);


#endif