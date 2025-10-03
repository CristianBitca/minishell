/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 10:40:19 by skirwan           #+#    #+#             */
/*   Updated: 2025/08/07 15:34:55 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

void	free_tokens(t_token *token)
{
	t_token	*temp;

	while (token)
	{
		temp = token;
		token = token->next;
		if (temp->value)
			free(temp->value);
		free(temp);
	}
}

int	tokenise(t_data *data, char *input)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(*lexer));
	lexer->pos = 0;
	lexer->line = input;
	lexer->line_size = ft_strlen(input);
	while (lexer->pos < lexer->line_size)
	{
		while (lexer->line[lexer->pos] == ' '
			|| lexer->line[lexer->pos] == '\t')
			lexer->pos++;
		if (is_operator(lexer->line[lexer->pos]) == 1)
			add_operator_token(data, lexer);
		else if (lexer->line[lexer->pos] != '\0')
		{
			if (add_word_token(data, lexer) == -1)
				return (free(lexer), -1);
		}
	}
	if (lexer->line)
		free(lexer->line);
	free(lexer);
	if (validate_tokens(data) == -1)
		return (-1);
	return (0);
}
