/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 20:56:10 by cbitca            #+#    #+#             */
/*   Updated: 2025/10/02 20:03:17 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(t_data *data, char *invalid_val)
{
	write (STDERR_FILENO, "syntax error near unexpected token '", 36);
	write (STDERR_FILENO, invalid_val, ft_strlen(invalid_val));
	write (STDERR_FILENO, "'\n", 2);
	data->exit_status = 2;
	return (-1);
}

// The only valid token after a redirection is a word. Following a pipe
// there cannot be another pipe because we are not handling the || operator.
// Also the first token cannot be a pipe, the last token also cannot be
// a pipe because we are not handling unclosed quotes. The last token
// also cannot be a redirection.
int	validate_tokens(t_data *data)
{
	t_token	*token;

	token = data->tokens;
	if (token == NULL)
		return (-1);
	if (token->type == PIPE)
		return (syntax_error(data, token->value));
	while (token->next != NULL)
	{
		if (token->type == REDIR_HEREDOC && token->next->type != WORD)
			return (syntax_error(data, token->next->value));
		if (token->type == REDIR_APPEND && token->next->type != WORD)
			return (syntax_error(data, token->next->value));
		if (token->type == REDIR_IN && token->next->type != WORD)
			return (syntax_error(data, token->next->value));
		if (token->type == REDIR_OUT && token->next->type != WORD)
			return (syntax_error(data, token->next->value));
		if (token->type == PIPE && token->next->type == PIPE)
			return (syntax_error(data, token->next->value));
		token = token->next;
	}
	if (token->type == PIPE || token->type == REDIR_APPEND
		|| token->type == REDIR_IN || token->type == REDIR_HEREDOC
		|| token->type == REDIR_OUT)
		return (syntax_error(data, "newline"));
	return (0);
}
