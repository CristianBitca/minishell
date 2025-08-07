/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 11:39:40 by skirwan           #+#    #+#             */
/*   Updated: 2025/08/07 15:35:38 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "lexer.h"

void	add_redir_token(t_data *data, t_lexer *lex)
{
	if (lex->line[lex->pos] == '>')
	{
		if (lex->line[lex->pos + 1] == '>')
		{
			add_token_back(&data->tokens, create_token(">>", REDIR_APPEND));
			lex->pos++;
		}
		else
			add_token_back(&data->tokens, create_token(">", REDIR_OUT));
	}
	else if (lex->line[lex->pos] == '<')
	{
		if (lex->line[lex->pos + 1] == '<')
		{
			add_token_back(&data->tokens, create_token("<<", REDIR_HEREDOC));
			lex->pos++;
		}
		else
			add_token_back(&data->tokens, create_token("<", REDIR_IN));
	}
}

void	add_word_token(t_data *data, t_lexer *lex)
{
	char	*string;
	char	end_quote;
	int		first_char;

	first_char = lex->pos;
	while ((lex->pos < lex->line_size)
		&& is_operator(lex->line[lex->pos] == 0)
		&& lex->line[lex->pos] != ' ')
	{
		if (lex->line[lex->pos] == '\'' || lex->line[lex->pos] == '"')
		{
			end_quote = lex->line[lex->pos];
			lex->pos++;
			while (lex->line[lex->pos] != end_quote
				&& (lex->pos < lex->line_size))
				lex->pos++;
			if (lex->line[lex->pos] != end_quote)
				(void)lex; //syntax error
		}
		else
			lex->pos++;
	}
	string = ft_substr(lex->line, first_char, (lex->pos - first_char));
}

void	add_operator_token(t_data *data, t_lexer *lexer)
{
	if (lexer->line[lexer->pos] == '|')
		add_token_back(&data->tokens, create_token("|", PIPE));
	else if (lexer->line[lexer->pos] == '<')
		add_redir_token(data, lexer);
	else if (lexer->line[lexer->pos] == '>')
		add_redir_token(data, lexer);
	lexer->pos++;
}
