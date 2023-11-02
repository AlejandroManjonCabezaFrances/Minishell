/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:29:49 by amanjon-          #+#    #+#             */
/*   Updated: 2023/11/02 17:42:24 by amanjon-         ###   ########.fr       */
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

/* ------ STRUCT SANDBOX LINKED LIST ------ */
typedef struct s_env
{
	char			*env_item;
	struct s_env	*next;
}	t_env;

/* ------ STRUCT ------ */
typedef struct s_process	t_process;
typedef struct s_inf		t_inf;
t_inf						g_info;

typedef struct s_process
{
	int					type_tokens;	// < << > >> | >& \0
	char				*content;
	struct s_process	*next;
}	t_process;

typedef struct s_inf				//para utilizar variable globales o estructuras globales
{
	char			**env;
	char 			*pwd;
	t_process		*tokens;
	int				signal_code;
	struct 	termios	termios;		//disable (ctrl + c) printing ^C
}	t_inf;							// variable global con tipo de dato 't_info'

/* -- DECLARATION VARIABLE GOBAL -- */
t_inf					g_info;

/* ------- MACROS ------- */
#define INIT_INT		-1  // TYPE_TOKENS & OTHERS ERROR
#define FALSE			0	//BOOLEAN
#define TRUE			1	//BOOLEAN
#define GREAT			3	//'>'
#define	LESS			4	//'<'
#define	APPEND			5	//'>>'
#define	HEREDOC			6	//'<<'
#define	GREATAMPERSAND	7	//'>&'
#define	PIPE			8	//'|'
#define	END				9	//'\0'

/*---------- OPERATORS ----------*/
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

/* ----------------- FUNCTION MINISHELL----------------- */
int			main(int argc, char **argv, char **env);
t_process	*ft_lstnew_mshell(void);
void		ft_lstadd_back_mshell(t_process **lst, t_process *new);
void		ft_lstclear_mshell(t_process **lst);
void		ft_signals(void);
void		ft_signal_interrupt(void);
void		ft_signal_reset_prompt(int signal);
void		ft_signal_quit(void);
int			ft_save_tokens_delimiters(t_process **process, char *line, int i);
int			ft_save_tokens_words(t_process **process, char *line, int i);
int			ft_tokens_delimiters(char *line, int i);
int			ft_tokenize(t_process **process, char *line);
int			ft_what_delimiter(char c);
int			ft_what_quotes(char c);
int			ft_is_space(char c);
void		ft_find_open_close_quotes(char *line, int *j, int *quote);
void		ft_print_lst(t_process *temp);


/*-------- SANDBOX 2 --------*/
char	*ft_strjoin_2(char *s1, char *s2);
void	ft_print_lst_2(t_env *temp);
void	ft_lstclear_mshell_2(t_env **lst);
t_env	*ft_lstnew_str_env(char *str_env);
void	ft_lstadd_back_str_env(t_env **envi, t_env *node);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_lstdelone_mshell(t_env *env_copy/* , void (*del)(void *) */);

/*-------- SANDBOX 2 GOOD FUNCTION--------*/
void	ft_replace_SHLVL(t_env **env_copy);
void	ft_find_and_delete_variable_env(t_env **env_copy, const char *var);
char	*ft_find_variable_env(t_env *env_copy, const char *var);
void	ft_linked_list_env(t_env **env_copy, char **env);
void	ft_print_double_pointer(char **env_array);
char	**ft_convert_linked_list_to_array(t_env *env_copy);

/*---------- TEST ----------*/
// void		ft_copy_env(t_inf *info);
// void		ft_get_env(t_inf *info, char **env);
// void		ft_when_env_is_null(t_inf *info);
// void		store_env_aux(t_inf *info, char **env);

#endif