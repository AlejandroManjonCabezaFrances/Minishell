/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 02:33:42 by marvin            #+#    #+#             */
/*   Updated: 2024/03/24 02:33:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	void	ft_lstadd_penultimate_str_env(t_env **envi, t_env *node)
{
	t_env	*aux;
	t_env	*last;

	aux = *envi;
	last = ft_lstlast_ms(*envi);
	if (*envi == NULL)
	{
		*envi = node;
		return ;
	}
	else
	{
		while (aux->next->next != NULL)
			aux = aux->next;
		aux->next->prev = node;
		aux->next->prev->prev = aux;
		aux->next = node;
		node->next = last;
	}
}

/**
 * Exports the variable already parsed and puts it in the
 * penultimate position as the terminal
 * @param	char *cmd, t_env *envi
 * @return	void
*/
void	ft_export_parsed_variable(char *cmd, t_env **envi)
{
	ft_lstadd_penultimate_str_env(envi, ft_lstnew_str_env(cmd));
}

/**
 * Splits arguments without '=', not numbers and creates two alphabetically
 * ordered lists
 * @param	t_env *envi, char *cmd
 * @return	 void
*/
static	int	ft_export_error_argv(char *cmd)
{
	int	i;

	i = -1;
	if (cmd != NULL)
	{
		while (cmd[++i])
		{
			if (!ft_isalpha(cmd[0]))
			{
				ft_putstr_fd("minishell: export: '", 2);
				ft_putstr_fd(cmd, 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				g_signal_code = 1;
				return (TRUE);
			}
		}
	}
	return (FALSE);
}

/**
 * The non-existing variable to be exported will be parsed.
 * @param	char **cmd, char *aux, int *fail
 * @return	var_parsed. Parsed mallocated string
*/
char	*ft_parser_arguments(char *cmd)
{
	int		i;
	int		len;
	int		start;
	char	*var_parsed;

	i = 0;
	if (ft_export_error_argv(cmd) == FALSE)
	{
		while (cmd[i] && cmd[i] != '=')
			i++;
		while (cmd[i] != ' ' && i >= 0)
			i--;
		i++;
		start = i;
		len = 0;
		while (cmd[i] && cmd[i] != ' ')
		{
			len++;
			i++;
		}
		var_parsed = ft_substr(cmd, start, len);
		return (var_parsed);
	}
	return (NULL);
}

/**
 * Look for a "=" in the received string
 * @param	char *str
 * @return	TRUE, FALSE
*/
int	ft_is_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (TRUE);
		i++;
	}
	return (FALSE);
}
