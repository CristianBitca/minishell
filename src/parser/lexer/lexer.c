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
	t_token	*temp;
	int		i;

	lex = ft_calloc(1, sizeof(t_lexer));
	if (!lex)
		return (0);
	lex->line = data->line;
	lex->size = ft_strlen(lex->line);
	tokenize(lex);
	temp = lex->first;
	while (temp)
	{
		printf("Token nr %d\n", i);
		printf("%s\n", temp->value);
		printf("%u\n", temp->type);
		temp = temp->next;
		i++;
	}
	return (lex);
}
