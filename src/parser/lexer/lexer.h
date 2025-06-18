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
	REDIR_OUY,
	REDIR_APPEND,
	REDIR_HEREDOC,
	AND,
	OR,
	SEMI,
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
	t_token	*first;
	t_token	*last;
}	t_lexer;

t_lexer	*lexer(t_data *data);

t_token	*new_token(t_tokentype type);
void	append_token(t_token **tokens, t_token *new);
t_token	*tokens_last(t_token *first);

#endif