/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 12:16:37 by skirwan           #+#    #+#             */
/*   Updated: 2025/08/08 14:04:23 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "minishell.h"

// expand.c
void	split_expand(char *input, t_expand *exp);
void	find_expansions(t_data *data, t_token *token);
void	expand(t_data *data);
void	free_exp_value(t_expand *exp);

// expand_env.c
void	check_qmark(t_expand *exp);
char	*insert_env(t_data *data, char *input);
char	*expand_exit_code(t_data *data, t_token *token, t_expand *exp);
char	*invalid_env_expansion(t_token *token, t_expand *exp);
char	*expand_env(t_data *data, t_token *token, t_expand *exp);
char	*expand_s_quote(t_token *token, t_expand *exp);
char	*expand_d_quote(t_data *data, t_token *token, t_expand *exp);

//word_splitting.c
void	insert_tokens(t_data *data, t_token *node, t_token *tokens);
char	*split_word(t_data *data, t_token *token, t_expand *exp, char *input);
int	check_tokens(t_data *data, char *input);

//expand_heredoc.c
char	*expand_delimiter(char *delimiter, int *exp_flag);
char	*expand_input(t_data *data, char *input, int *exp_flag);

#endif
