/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:48:26 by cbitca            #+#    #+#             */
/*   Updated: 2025/06/09 17:48:27 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../include/minishell.h"
# include "lexer/lexer.h"

typedef struct s_token	t_token;
typedef struct s_lexer	t_lexer;
typedef struct s_data	t_data;

void	parse(t_data *data);
void	validate_tokens(t_lexer *lex);

void	expand(t_data *data, t_lexer *lex);

#endif