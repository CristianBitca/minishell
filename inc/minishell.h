/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:48:25 by cbitca            #+#    #+#             */
/*   Updated: 2025/09/17 12:47:23 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <bits/types/sigset_t.h>
# include <signal.h>
# include "libft.h"

typedef enum e_tokentype
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	DELETE,
}	t_tokentype;

typedef struct s_token
{
	t_tokentype		type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_lexer
{
	char	*line;
	int		line_size;
	int		start;
	int		pos;
}	t_lexer;

typedef struct s_expand
{
	char	*before;
	char	*expand;
	char	*after;
	int		l_before;
	int		l_expand;
	int		l_after;
	int		pos;
	int		start;
	int		size;
	int		exp_heredoc;
}	t_expand;

typedef struct s_prcs
{
	char	**argv;
	int		infilefd;
	int		outfilefd;
}	t_prcs;

typedef struct s_env_var
{
	struct s_env_var	*next;
	char				*key;
	char				*value;
}	t_env_var;

typedef struct s_data
{
	struct s_token		*tokens;
	struct s_prcs		**processes;
	t_env_var			*env;
	int					exit_status;
}	t_data;

void	cmd_line(t_data *data);
void	print_tokens(t_data *data);

#endif
