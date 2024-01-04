/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:29:49 by amanjon-          #+#    #+#             */
/*   Updated: 2024/01/04 15:37:09 by amanjon-         ###   ########.fr       */
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
typedef struct s_token		t_token;
typedef struct s_scmd		t_scmd;
// typedef struct s_inf		t_inf;
// t_inf						g_info;

typedef struct s_token
{
	int				type;				// < << > >> | >& \0
	char			*content;
	struct s_token	*next;
}	t_token;

typedef struct s_scmd
{
	char			*cmd;
	char			**cmd_args;
	int				arg_count;
	struct s_scmd	*next;
}	t_scmd;

typedef struct s_inf				//para utilizar variable globales o estructuras globales
{
	char			**env;
	char 			*pwd;
	//t_process		*tokens;
	int				signal_code;
	struct 	termios	termios;		//disable (ctrl + c) printing ^C
}	t_inf;							// variable global con tipo de dato 't_info'

/* ------ STRUCT SANDBOX LINKED LIST ------ */
typedef struct s_env
{
	char			*env_item;
	struct s_env	*next;
}	t_env;

/* ------ ENUMS ------ */
enum e_boolean {
	FALSE = 0,
	TRUE,
};

enum e_tokens {
	IN_REDIR = 2,
	OUT_REDIR,
	HEREDOC,
	APPEND,
	PIPE,
	WORD,
	QUOTED_WORD
};

enum e_quotes {
	SINGLE_QUOTE = 9,
	DOUBLE_QUOTE,
};

enum e_error {
	INIT_INT = 11,
	QUOTING_ERR,
	READLINE_ERR
};

/* ------ MAIN ------ */
void	ft_disable_ctrl_c_printing_chars(t_inf inf);
char	**copy_env(char **envp);

/* ------ LEXER ------ */
int		lexer(t_token **token_list, char *input, char **env);
int		handle_quotes(t_token **token_list, char *input, int i, char **env);
int		handle_operators(t_token **token_list, char *input, int i);
int		handle_words(t_token **token_list, char *input, int i);
int		handle_dsign(t_token **token_list, char *input, int i, char **env);
int		operator_type(char *input, int i);
int		is_operator(char c);
int		is_quote(char c);
int		is_space(char c);
int		is_dsign(char c);
char	*quoted_dsign(char *str, char **env);
char	*find_var(char *var, char **env);

/* ------ PARSER ------ */
void	parse(t_token *token, t_scmd **scmds_list);

/* ------ LISTS ------ */
t_token	*ms_lstnew(void);
t_scmd	*ms_lstnew_cmd(char *content);
void	ms_lstadd_back(t_token **list, t_token *new);
void	ms_lstadd_back_smcd(t_scmd **list, t_scmd *new);
void	ms_lstclear(t_token **list);
void	ms_print_lst(t_token *token);
int		ms_check_lst(t_token *token, int type);

/* ------ ERROR ------ */
void	panic(int err, t_token **list, t_token *token);

/* ------ SIGNALS ------ */
void	ft_signals(void);
void	ft_signal_interrupt(void);
void	ft_signal_reset_prompt(int signal);
void	ft_signal_quit(void);

#endif