/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:35:21 by cbitca            #+#    #+#             */
/*   Updated: 2025/06/09 17:35:23 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer	*lexer(t_data *data)
{
	t_lexer	*lex;

	lex = ft_calloc(sizeof(t_lexer), sizeof(t_lexer));
	if (!lex)
		return (0);
	while (data->line[lex->pos])
	{
		if (data->line[lex->pos] == ' ')
			lex->start = lex->pos++;
		else
		{
			append_token(&lex->first, new_token(WORD));
			while (data->line[lex->pos] != ' ' && data->line[lex->pos])
				lex->pos++;
		}
	}
	return (lex);
}
