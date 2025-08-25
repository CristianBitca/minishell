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
void	free_exp(t_expand *exp);
void	split_expand(t_token *token, t_expand *exp);
void	find_expansions(t_data *data, t_token *token);
void	expand(t_data *data);

// expand_env.c
void	expand_exit_code(t_data *data, t_token *token, t_expand *exp);
void	invalid_env_expansion(t_token *token, t_expand *exp);
void	valid_expansion(t_data *data, t_token *token, char *to_expand);
void	expand_env(t_data *data, t_token *token, t_expand *exp);
void	expand_s_quote(t_token *token, t_expand *exp);
void	expand_d_quote(t_token *token, t_expand *exp);

//word_splitting.c
void	insert_token(t_token *node, char *value);
void	tok_branch(t_token *node, char **expansion, char *post_expand, int join_back);
void	split_word(t_token *token, char *expand_value, char *post_expand);
#endif
