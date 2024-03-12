/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:29:49 by amanjon-          #+#    #+#             */
/*   Updated: 2024/03/12 12:48:36 by amanjon-         ###   ########.fr       */
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
typedef struct s_info		t_info;
typedef struct s_scmd		t_scmd;
typedef struct s_inf		t_inf;
// int							g_signal_code;

typedef struct s_token
{
	int				type;				// < << > >> | WORD, QUOTED_WORD
	char			*content;
	struct s_token	*next;
}	t_token;

/* ------ STRUCT LINKED LIST DECLARE------ */
typedef struct s_declare
{
	char			*content;
	struct s_declare	*next;
	struct s_declare	*prev;
}	t_declare;

/* ------ STRUCT LINKED LIST ------ */
typedef struct s_env
{
	char			**env_n;
	int				flag;
	// char			*cwd;
	char			*content;
	char			*pwd;
	char			*old_pwd;
	t_declare		*declare;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;


typedef struct s_info
{
	int				pipe_nbr;
	char			*path;
	char			**bin_paths;
	char			**env_cpy;
	t_env			*envi;
	t_env			*declare;
}	t_info;

typedef struct s_scmd
{
	int				infile;
	int				outfile;
	int				heredoc;
	char			*cmd_name;
	char			*cmd_path;
	char			**cmd_args;
	t_token			*wordlist;
	struct s_scmd	*next;
}	t_scmd;

typedef struct s_inf				//para utilizar variable globales o estructuras globales
{
	// char			**env_n;
	char 			*cwd;
	// int				signal_code;
	struct 	termios	termios;		//disable (ctrl + c) printing ^C
}	t_inf;


/* ------ ENUMS ------ */
enum e_boolean
{
	FALSE = 0,
	TRUE,
};

enum e_tokens
{
	IN_REDIR = 2,
	OUT_REDIR,
	HEREDOC,
	APPEND,
	PIPE,
	WORD,
	QUOTED_WORD,
	FILENAME,
	EOF_N
};

enum e_quotes
{
	SINGLE_QUOTE = 11,
	DOUBLE_QUOTE
};

enum e_error
{
	INIT_INT = 13,
	QUOTING_ERR,
	READLINE_ERR,
	PARSE_ERR,
	INFILE_ERR,
	OUTFILE_ERR,
	MALLOC_ERR,
	COMMAND_ERR,
	PIPE_ERR,
	FORK_ERR
};

/* ------ GLOBAL ------ */
extern int	exit_status;

/* ------ MAIN ------ */
void	disable_ctrl_c_printing_chars(void);
void	init_struct(t_env **envi, t_inf *info);
int		check_argc(int argc);

// void	shell_operation(char *line, t_token *list, t_scmd *scmds, t_info info);
void	shell_operation(t_env **envi, char *line, t_token *list, t_scmd *scmds, t_info info);

/* ------ LEXER ------ */
int		lexer(t_token **token_list, char *input);
int		handle_operators(t_token **token_list, char *input, int i);
int		handle_words(t_token **token_list, char *input, int i);
int		operator_type(char *input, int i);
int		is_operator(char c);
int		is_qte(char c);
int		is_space(char c);
int		is_dsign(char c);

/* ------ PARSER ------ */
t_token	*create_scmd(t_token *token, t_scmd **scmds_list);
void	create_node(t_token *token, t_token **wordlist);
void	store_cmdargs(t_scmd *scmd);
void	handle_redir(t_scmd **scmds_list);
void	assign_filenames(t_token **token_list);
void	expand_var(t_scmd **scmds_list, char **env);
void	check_dsign(t_scmd *scmd, char **env);
void	remove_quotes(t_scmd **scmds_list);
void	check_quotes(t_scmd *scmd);
char	*unquoted_str(char *unquoted, char *str, int i, int j);
char	*unquote(char *str);
char	*expand(char *str, char **env);
char	*buffer_var(char *source, int start, int end, char **env);
char	*expand_dsign(char *str, char **env, int start);
char	*quoted_dsign(char *str, char **env, int i);
int		count_flen(char *str, int i);
int		closing_quote(char *str, int i);
int		build_cmd(t_scmd *scmd);
int		find_cmds(t_scmd **scmds_list);
int		open_heredoc(t_scmd *scmd, t_token *token);
int		open_append(t_scmd *scmd, t_token *token);
int		open_outfile(t_scmd *scmd, t_token *token);
int		open_infile(t_scmd *scmd, t_token *token);
int		check_files(t_scmd *scmd);
int		build_scmdlist(t_token **token_list, t_scmd **scmds_list, t_info *info);
int		is_redir(int type);
int		check_pipe(t_token *token);
int		check_redir(t_token *token);
int		check_syntax(t_token **token_list);
int		parser(t_token **token_list, t_scmd **scmds_list, t_info *info);

/* ------ EXECUTER ------ */
void	ft_dup(int old_fd, int new_fd);

void	check_cmds(t_scmd **scmds_list, t_info *info);
// void	exec_child(t_scmd *scmd, t_info *info, int upstream, int *pipe_fd);
void	exec_child(t_env **envi, t_scmd *scmd, t_info *info, int upstream, int *pipe_fd);

// void	last_child(t_scmd *scmd, t_info *info, int upstream);
void	last_child(t_env **envi, t_scmd *scmd, t_info *info, int upstream);

// void	ft_builtin(t_info *info, char **args);
void	ft_builtin(t_env **envi, char **args, t_info *info);
void	ft_builtins(char **cmd, t_env **envi, char **env);

void	parent_close(int fd_1, int fd_2, t_scmd *scmd);
int		check_builtin(t_scmd *scmd);

// int		exec_command(t_scmd *scmd, t_info *info, int upstream, int *pipe_fd);
int		exec_command(t_env **envi, t_scmd *scmd, t_info *info, int upstream, int *pipe_fd);

// int		last_command(t_scmd *scmd, t_info *info, int upstream);
int		last_command(t_env **envi, t_scmd *scmd, t_info *info, int upstream);

// int		exec_cmds(t_scmd **scmds_list, t_info *info);
int		exec_cmds(t_env **envi, t_scmd **scmds_list, t_info *info);
int		get_cmd(t_scmd *scmds_list, t_info *info);
int		check_path(t_scmd *scmd);

// int		executer(t_scmd **scmds_list, t_info *info);
int		executer(/* t_env **envi,  */t_scmd **scmds_list, t_info *info);

/* ------ LISTS ------ */
t_token	*ms_lstnew(void);
t_scmd	*ms_cmdnew(void);
void	ms_cmdadd_back(t_scmd **list, t_scmd *new);
void	ms_lstadd_back(t_token **list, t_token *new);
void	ms_lstclear(t_token **list);
void	ms_cmdclear(t_scmd **list);
void	ms_print_lst(t_token *token);
void	ms_print_cmdlst(t_scmd *sequence);
void	ms_close_fds(t_scmd **list);

/* ------ ERROR ------ */
void	panic(int err, t_token **list, t_token *token);
void	free_array(char **str);
void	free_info(t_info info);

/* ------ SIGNALS ------ */
void	ft_signals(void);
void	ft_signal_interrupt(void);
void	ft_signal_reset_prompt(int signal);
void	ft_signal_quit(void);

/* ------ ENV ------ */
char	**copy_env(char **envp);
char	*get_path(char **env);
char	*find_var(char *varname, char **env);

/* ------ ENVIRO ------ */
t_env	*ft_lstnew_str_env(char *str_env);
void	ft_lstadd_back_str_env(t_env **envi, t_env *node);
void	ft_linked_list_env(t_env **envi, char **env);

/* ------ ENVI ------ */
// char	**copy_env(char **env);
// void	ft_when_env_is_null(t_inf *info);
// void	ft_env_is_null(t_env *envi, t_inf *info, char **env);
// void	ft_when_env_is_null(t_env **envi, t_inf *info);

/* ------ SANDBOX2 ------ */
// int		ft_strcmp(const char *s1, const char *s2);
// // char	*ft_strjoin_2(char *s1, char *s2);
// void	ft_lstclear_mshell_2(t_env **lst);
// void	ft_replace_SHLVL(t_env **env_copy);
// void	ft_find_and_delete_variable_env(t_env **env_copy, const char *var);
// char	*ft_find_content_var_env(t_env *env_copy, char *var);
// void	ft_print_double_pointer(char **env_array);
// char	**ft_convert_linked_list_to_array(t_env *env_copy);
// void	ft_lstadd_penultimate_str_env(t_env **envi, t_env *node);
// t_env	*ft_lstnew_penultimate_str_env(char *str_env);

// char	*ft_itoa(int nbr);
// int		ft_atoi(const char *str);
// size_t	ft_strlen(const char *str);
// char	*ft_strdup(const char	*s1);
// int		ft_strncmp(const char *s1, const char *s2, size_t n);
// void	ft_lstdelone_mshell(t_env *env_copy);

/* ----------- BUILTINS ----------- */
// void		ft_builtins(char **cmd, t_env **envi, char **env);

	/* ------ ECHO ------ */
void	ft_echo(char **cmd);
	/* ------ PWD ------ */
void	ft_pwd(char **cmd);
	/* ------ EXPORT ------ */
void	ft_export(char **cmd, t_env **envi);
	/* ------ UNSET ------ */
void	ft_unset(char **cmd, t_env **envi);
	/* ------ CD ------ */
int		ft_cd(char **cmd, t_env *envi, char **env);
	/* ------ ENV ------ */
void	ft_env(t_env **envi, char **cmd);
	/* ------ EXIT ------ */
void    ft_exit(char **cmd, t_env *envi);

/* ------ UTILS_ALEX ------ */
int			ft_strcmp(const char *s1, const char *s2);
void		ft_linked_list_env(t_env **envi, char **env);
void		ft_print_lst_2(t_env *temp);
void		del_ms(void *content);
void		ft_lstdelone_ms(t_env *lst, void (*del_ms)(void *));
t_env		*ft_lstlast_ms(t_env *lst);
t_env		*ft_lstnew_str_env(char *str_env);
void		ft_lstadd_back_str_env(t_env **envi, t_env *node);
void		ft_replace_node(t_env *envi, char *str, char *pwd_oldpwd);
void		ft_simulate_env_i_minishell(t_env **envi);
void		ft_linked_list_env_lst_to_lst(t_declare **declare, t_env **envi);
void		ft_linked_list_env_to_declare(t_declare **declare, char **env);
void		ft_print_lst_2_to_declare(t_declare *temp);
void		ft_lstadd_back_str_env_to_declare(t_declare **declare, t_declare *node);
t_declare	*ft_lstnew_str_env_to_declare(char *str_env);
void		ft_print_double_pointer(char **env_array);

#endif