/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:29:49 by amanjon-          #+#    #+#             */
/*   Updated: 2023/10/16 15:16:56 by amanjon-         ###   ########.fr       */
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
#include <readline/readline.h>	//función readline -prompt-
#include <readline/history.h>	//readline() antiguo
#include <signal.h> 			//función signal() / sigaction()
#include <termios.h>			//función tcsetattr() para ctrl+c '^C'

/* ---------------- PATH ---------------- */
# include "../libft/Libft/include/libft.h"
# include "../libft/ft_printf/include/ft_printf.h"
# include "../libft/Gnl/include/get_next_line.h"


/* ------ STRUCT ------ */
typedef struct s_node				//para funciones de listas
{
	char			*content;
	struct s_node	*next;
}	t_node;

typedef struct s_process
{
	char			*line;
	int				type_tokens;	// < << > >> | >& \0
	int				type_quotes;
	t_node			*tokens;
}	t_process;

typedef struct s_info				//para utilizar variable globales o estructuras globales
{
	int				signal_code;
	struct 	termios	termios;		//disable (ctrl + c) printing ^C
}	t_inf;							// variable global con tipo de dato 't_info'

/* -- DECLARATION VARIABLE GOBAL -- */
t_inf					g_info;

/* ------ MACROS ------ */
#define FALSE			0
#define TRUE			1
#define GREAT			3	//'>'
#define	LESS			4	//'<'
#define	APPEND			5	//'>>'
#define	HEREDOC			6	//'<<'
#define	GREATAMPERSAND	7	//'>&'
#define	PIPE			8	//'|'
#define	END				9	//'\0'


/*--delimiters --*/
#define SINGLE_QUOTES	10	//'\''
#define DOUBLE_QUOTES	11	//"""

// enum delimeters {
//     GREAT = 3,
//     LESS = 4,
//     APPEND = 5,
//     HEREDOC = 6,
//     GREATAMPERSAND = 7,
//     PIPE = 8,
//     END = 9,
// 	SIMPLE_QUOTES = 10,
// 	DOUBLE_QUOTES = 11
// };

/* ----------------- FUNCTION ----------------- */
int			main(int argc, char **argv, char **env);
t_node		*ft_lstnew_mshell(char *content);
void		ft_lstadd_back_mshell(t_node **lst, t_node *new);
void		ft_lstclear_mshell(t_node **lst);
void		ft_signals(void);
void		ft_signal_interrupt(void);
void		ft_signal_reset_prompt(int signal);
void		ft_signal_quit(void);
void		ft_save_tokens_delimiters(t_process *process, int *i);
int			ft_tokens_delimiters(t_process *process, int *i);
int			ft_save_tokens_words(t_process *process, int i);
int			ft_tokenize(t_process *process);
int			ft_what_delimiter(char c);
int			ft_what_quotes(char c);
int			ft_is_space(char c);
void		ft_print_lst(t_node *temp);
void		ft_find_open_close_quotes(t_process *process, int *j, int *type_quotes);

#endif