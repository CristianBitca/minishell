/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:52:39 by cbitca            #+#    #+#             */
/*   Updated: 2025/09/01 19:52:41 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"

char	*expand_delimiter(char *delimiter, int *exp_flag)
{
	t_expand	*exp;

	exp = ft_calloc(sizeof(t_expand), 1);
	exp->size = ft_strlen(delimiter);
	if (ft_strchr(delimiter, '\'') || ft_strchr(delimiter, '"'))
		*exp_flag = 1;
	else
		*exp_flag = 0;
	while (delimiter[exp->pos])
	{
		if (delimiter[exp->pos] == '\'')
			break;
		else if (delimiter[exp->pos] == '"')
			break;
		else
			exp->pos++;
	}
	if (delimiter[exp->pos] == '\'' || delimiter[exp->pos] == '"')
	{
		split_expand(delimiter, exp);
		delimiter = expand_s_quote(delimiter, exp);
	}
	return (delimiter);
}

char	*expand_input(t_data *data, char *input, int *exp_flag)
{
	t_expand	*exp;

	exp = ft_calloc(sizeof(t_expand), 1);
	exp->size = ft_strlen(input);
	while (input[exp->pos])
	{
		if (input[exp->pos] == '$' && input[exp->pos + 1] && exp_flag)
		{
			(exp->exp_heredoc = 1, split_expand(input, exp));
			input = expand_env(data, 0, input, exp);
		}
		else
			exp->pos++;
	}
	free_exp(data, exp);
	return (input);
}
