/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 20:56:10 by cbitca            #+#    #+#             */
/*   Updated: 2025/07/29 20:56:13 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	syntax(t_token *token)
{
	if (token->type == PIPE || token->type == AND
		|| token->type == OR || token->type == SEMI)
	{
		printf("%d\n", token->prev->type);
		// if (token->prev->type != WORD && token->next->type != WORD)
		// 	printf("not word");
		// else
		// 	printf("not word");
	}
	return (0);
}

void	validate_tokens(t_lexer *lex)
{
	t_token	*temp;
	int		i;

	temp = lex->first;
	i = 0;
	while (temp)
	{
		printf("Token nr %d before check\n", i);
		printf("%s\n", temp->value);
		printf("%u\n", temp->type);
		syntax(temp);
		// expansion();
		printf("Token nr %d after check\n", i);
		printf("%s\n", temp->value);
		printf("%u\n", temp->type);
		temp = temp->next;
		i++;
	}
}
