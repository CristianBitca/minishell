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

int	syntax_check(t_tokentype type)
{
	if (type == WORD || type == VAR
		|| type == S_QUATE || type == D_QUATE)
		return (0);
	return (1);
}

int	syntax(t_token *token)
{
	if (token->type == OPEN_QUATE)
		return (print_error(ERR_QUOTE));
	else if (token->type != WORD)
	{
		if (token->type == REDIR_APPEND || token->type == REDIR_HEREDOC
			|| token->type == REDIR_IN || token->type == REDIR_OUT)
		{
			if (syntax_check(token->next->type))
				return (print_error(ERR_SYNTAX));
		}
		if (token->type == OR || token->type == PIPE || token->type == OPTION)
		{
			if (syntax_check(token->next->type)
				&& (token->prev == NULL || !syntax_check(token->prev->type)))
				return (print_error(ERR_SYNTAX));
		}
	}
	return (1);
}

void	validate_tokens(t_lexer *lex)
{
	t_token	*temp;

	temp = lex->first;
	while (temp)
	{
		if (!syntax(temp))
			break ;
		temp = temp->next;
	}
}
