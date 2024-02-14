/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:29:49 by amanjon-          #+#    #+#             */
/*   Updated: 2024/02/14 14:00:14 by marvin           ###   ########.fr       */
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
# include <limits.h>

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
typedef struct s_inf		t_inf;
extern int 					g_signal_code;


typedef struct s_token
{
	int				type;				// < << > >> | WORD, QUOTED_WORD
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
	// int				signal_code;
	struct 	termios	termios;		//disable (ctrl + c) printing ^C
}	t_inf;

/* ------ STRUCT SANDBOX LINKED LIST ------ */
typedef struct s_env
{
	char			*content;
	char			*pwd;
	char			*old_pwd;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_cmd
{
	char 			**command;
	char			*prompt;
}	t_cmd;

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
void	disable_ctrl_c_printing_chars(t_inf inf);
char	**copy_env(char **env);
void	init_struct(t_inf *inf);
int		check_argc(int argc);

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
t_token	*lstnew_ms(void);
t_scmd	*lstnew_ms_cmd(char *content);
void	lstadd_back_ms(t_token **list, t_token *new);
void	lstadd_back_ms_smcd(t_scmd **list, t_scmd *new);
void	lstclear_ms(t_token **list);
void	print_lst_ms(t_token *token);
int		check_lst_ms(t_token *token, int type);

/* ------ ERROR ------ */
void	panic(int err, t_token **list, t_token *token);

/* ------ SIGNALS ------ */
void	ft_signals(void);
void	ft_signal_interrupt(void);
void	ft_signal_reset_prompt(int signal);
void	ft_signal_quit(void);
void	ft_set_signals_noninteractive(void); // new
void	ft_signal_print_newline(int signal); // new

/* ------ ENV ------ */
t_env	*ft_lstnew_str_env(char *str_env);
void	ft_lstadd_back_str_env(t_env **envi, t_env *node);
void	ft_linked_list_env(t_env **envi, char **env);

/* ------ ENVI ------ */
char	**copy_env(char **env);
void	ft_when_env_is_null(t_inf *info);
void	ft_get_env(t_inf *info, char **env);

/* ------ SANDBOX2 ------ */
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin_2(char *s1, char *s2);
void	ft_lstclear_mshell_2(t_env **lst);
void	ft_replace_SHLVL(t_env **env_copy);
void	ft_find_and_delete_variable_env(t_env **env_copy, const char *var);
char	*ft_find_content_var_env(t_env *env_copy, char *var);
void	ft_print_double_pointer(char **env_array);
char	**ft_convert_linked_list_to_array(t_env *env_copy);
void	ft_lstadd_penultimate_str_env(t_env **envi, t_env *node);
t_env	*ft_lstnew_penultimate_str_env(char *str_env);

char	*ft_itoa(int nbr);
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char	*s1);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_lstdelone_mshell(t_env *env_copy);

/* ----------- BUILTINS ----------- */
void		ft_builtins(char **cmd, t_env *envi);

	/* ------ ECHO ------ */
void	ft_echo(char **cmd);
	/* ------ PWD ------ */
void	ft_pwd(char **cmd);
	/* ------ EXPORT ------ */
void	ft_export(char **cmd, t_env *envi);
	/* ------ UNSET ------ */
void	ft_unset(char **cmd, t_env *envi);
	/* ------ CD ------ */
void	ft_cd(char **cmd, t_env *envi);
	/* ------ ENV ------ */
void	ft_env(t_env *envi);

/* ------ UTILS ------ */
int		ft_strcmp(const char *s1, const char *s2);
void	ft_linked_list_env(t_env **envi, char **env);
void	ft_print_lst_2(t_env *temp);
void	dele(void *content);
void	ft_lstdelone_ms(t_env *lst, void (*del)(void *));
t_env	*ft_lstlast_ms(t_env *lst);
t_env	*ft_lstnew_str_env(char *str_env);
void	ft_lstadd_back_str_env(t_env **envi, t_env *node);

#endif