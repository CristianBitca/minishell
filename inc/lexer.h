/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 10:40:34 by skirwan           #+#    #+#             */
/*   Updated: 2025/08/08 11:53:06 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

// token_list_utils.c
t_token *create_token(char *value, t_tokentype type);
t_token *last_token(t_token *first_token);
void	add_token_back(t_token **token_list, t_token *new_token);

// is_operator.c
int		is_operator(char c);

// create_tokens.c
void	add_redir_token(t_data *data, t_lexer *lex);
void	add_operator_token(t_data *data, t_lexer *lexer);
int		handle_quotes(t_lexer *lex, char end_quote);
int		add_word_token(t_data *data, t_lexer *lexer);

// tonkenise.c
int	tokenise(t_data *data, char *input);
void	free_tokens(t_token *token);

// validate_tokens.c
int	syntax_error(char *invalid_val);
int	validate_tokens(t_data *data);

#endif
