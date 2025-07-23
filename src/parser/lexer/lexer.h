/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:35:05 by cbitca            #+#    #+#             */
/*   Updated: 2025/06/09 17:35:07 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef LEXER_H
# define LEXER_H

# include "../../../include/minishell.h"

typedef struct s_data	t_data;

typedef enum e_tokentype
{
	WORD,
	PIPE,
	VAR,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	S_QUATE,
	D_QUATE,
	OPEN_QUATE,
	AND,
	OR,
	OPTION,
}	t_tokentype;

typedef struct s_token
{
	t_tokentype		type;
	struct s_token	*next;
	struct s_token	*prev;
	char			*value;
}	t_token;

typedef struct s_lexer
{
	int		pos;
	int		start;
	int		size;
	char	*line;
	t_token	*first;
	t_token	*last;
}	t_lexer;

t_lexer	*lexer(t_data *data);

t_token	*new_token(char *value, t_tokentype type);
void	append_token(t_token **tokens, t_token *new);
t_token	*tokens_last(t_token *first);

int		append_operator(t_lexer *lex);
int		is_operator(t_lexer *lex);
void	append_redir(t_lexer *lex);
void	append_quote(t_lexer *lex);
void	append_var(t_lexer *lex);
void	append_option(t_lexer *lex);



void	tokenize(t_lexer *lex);

#endif