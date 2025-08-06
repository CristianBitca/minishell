/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:25:25 by cbitca            #+#    #+#             */
/*   Updated: 2025/08/04 17:25:27 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*expand_var(t_data *data, t_token *token)
{
	char	*buffer;

	printf("THis is var: %s\n", &token->value[1]);
	if (token->value[0] != '$')
		return (printf("FAIL TO EXPAND VAR\n"), token->value);
	printf("LEnght of value: %ld\n", ft_strlen(token->value));
	buffer = find_env(data->env, &token->value[1]);
	return (buffer);
}

void	expand(t_data *data, t_lexer *lex)
{
	t_token	*temp;

	temp = lex->first;
	while (temp)
	{
		if (temp->type == VAR)
			expand_var(data, temp);
		temp = temp->next;
	}
}