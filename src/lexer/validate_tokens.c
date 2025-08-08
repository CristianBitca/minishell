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
	write (2, "syntax error near unexpected token '", 36);
	write (2, invalid_val, ft_strlen(invalid_val));
	write (2, "\n", 1);
	return (0);
}

int	validate_tokens(t_data *data)
{
	t_token *temp;
	int		i;

	temp = data->tokens;
	while (temp->next != NULL)
	{
		if (temp->type == REDIR_HEREDOC && temp->next->type != WORD)
			return (syntax_error(temp->next->value));
		if (temp->type == REDIR_APPEND && temp->next->type != WORD)
			return (syntax_error(temp->next->value));
		if (temp->type == REDIR_IN && temp->next->type != WORD)
			return (syntax_error(temp->next->value));
		if (temp->type == REDIR_OUT && temp->next->type != WORD)
			return (syntax_error(temp->next->value));
		if (temp->type == PIPE && temp->next->type == PIPE)
			return (syntax_error(temp->next->value));
		temp = temp->next;
	}
	return (1);
}
