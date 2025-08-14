/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 20:56:10 by cbitca            #+#    #+#             */
/*   Updated: 2025/08/08 11:45:36 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(char *invalid_val)
{
	write (2, "syntax error near unexpected token `", 36);
	write (2, invalid_val, ft_strlen(invalid_val));
	write (2, "'\n", 2);
	return (0);
}

int	validate_tokens(t_data *data)
{
	t_token *token;

	token = data->tokens;
	while (token->next != NULL)
	{
		if (token->type == REDIR_HEREDOC && token->next->type != WORD)
			return (syntax_error(token->next->value));
		if (token->type == REDIR_APPEND && token->next->type != WORD)
			return (syntax_error(token->next->value));
		if (token->type == REDIR_IN && token->next->type != WORD)
			return (syntax_error(token->next->value));
		if (token->type == REDIR_OUT && token->next->type != WORD)
			return (syntax_error(token->next->value));
		if (token->type == PIPE && token->next->type == PIPE)
			return (syntax_error(token->next->value));
		token = token->next;
	}
	return (1);
}
