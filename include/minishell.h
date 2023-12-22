/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:29:49 by amanjon-          #+#    #+#             */
/*   Updated: 2023/12/22 12:59:34 by amanjon-         ###   ########.fr       */
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

/* -- DECLARATION VARIABLE GOBAL -- */
t_inf					g_info;

/* ------ STRUCT ------ */
typedef struct s_token		t_token;
typedef struct s_inf		t_inf;
t_inf						g_info;

typedef struct s_token
{
	int				type;				// < << > >> | >& \0
	char			*content;
	struct s_token	*next;
}	t_token;

typedef struct s_inf				//para utilizar variable globales o estructuras globales
{
	char			**env;
	char 			*pwd;
	t_process		*tokens;
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
	WORD
};

enum e_quotes {
	SINGLE_QUOTE = 8,
	DOUBLE_QUOTE,
};

enum e_error {
	INIT_INT = 10,
	QUOTING_ERR,
	READLINE_ERR
};

/* ------ MAIN ------ */
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
void	parser(t_token **token_list);
void	parse_cmd(t_token **token_list);

/* ------ LISTS ------ */
t_token	*ms_lstnew(void);
void	ms_lstadd_back(t_token **list, t_token *new);
void	ms_lstclear(t_token **list);
void	ms_print_lst(t_token *token);
int		ms_check_lst(t_token *token, int type);

/* ------ UTILS ------ */
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char	*s1);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_join(char *dest, char *s1, char *s2);

/* ------ ERROR ------ */
void	panic(int err, t_token **list, t_token *token);





/* ------------------------------------- FUNCIONES ANTIGUA MINISHELL---------------------------------- */

/* ----------------- FUNCTION MINISHELL----------------- */
// int			main(int argc, char **argv, char **env);
// t_process	*ft_lstnew_mshell(void);
// void		ft_lstadd_back_mshell(t_process **lst, t_process *new);
// void		ft_lstclear_mshell(t_process **lst);
// void		ft_signals(void);
// void		ft_signal_interrupt(void);
// void		ft_signal_reset_prompt(int signal);
// void		ft_signal_quit(void);
// int			ft_save_tokens_delimiters(t_process **process, char *line, int i);
// int			ft_save_tokens_words(t_process **process, char *line, int i);
// int			ft_tokens_delimiters(char *line, int i);
// int			ft_tokenize(t_process **process, char *line);
// int			ft_what_delimiter(char c);
// int			ft_what_quotes(char c);
// int			ft_is_space(char c);
// void		ft_find_open_close_quotes(char *line, int *j, int *quote);
// void		ft_print_lst(t_process *temp);


// /*-------- SANDBOX 2 --------*/
// char	*ft_strjoin_2(char *s1, char *s2);
// void	ft_print_lst_2(t_env *temp);
// void	ft_lstclear_mshell_2(t_env **lst);
// t_env	*ft_lstnew_str_env(char *str_env);
// void	ft_lstadd_back_str_env(t_env **envi, t_env *node);
// int		ft_strncmp(const char *s1, const char *s2, size_t n);
// void	ft_lstdelone_mshell(t_env *env_copy/* , void (*del)(void *) */);

// /*-------- SANDBOX 2 GOOD FUNCTION--------*/
// void	ft_replace_SHLVL(t_env **env_copy);
// void	ft_find_and_delete_variable_env(t_env **env_copy, const char *var);
// char	*ft_find_var_env(t_env *env_copy, char *var);
// void	ft_linked_list_env(t_env **env_copy, char **env);
// void	ft_print_double_pointer(char **env_array);
// char	**ft_convert_linked_list_to_array(t_env *env_copy);

/*---------- TEST ----------*/
// void		ft_copy_env(t_inf *info);
// void		ft_get_env(t_inf *info, char **env);
// void		ft_when_env_is_null(t_inf *info);
// void		store_env_aux(t_inf *info, char **env);

#endif