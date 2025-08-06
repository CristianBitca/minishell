/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:40:33 by cbitca            #+#    #+#             */
/*   Updated: 2025/06/09 17:40:34 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parse(t_data *data)
{
	t_lexer	*lex;

	lex = lexer(data);
	validate_tokens(lex);
	expand(data, lex);
	(void)lex; 
}