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

char	*expand_var(t_data *data, char *var)
{
	char	*buffer;

	if (var[0] == '?')
	{
		printf("EXIT code\n");
		// buffer = ft_strjoin(buffer, &var[1]);
	}
	else
		buffer = find_env(data->env->next, var);
	if (!buffer)
		buffer = ft_strdup("");
	return (buffer);
}

char	*exapnd_s_quote(char *value)
{

}

// char	*expand_d_quote()

// char	*expand_word()

void	expand(t_data *data, t_lexer *lex)
{
	t_token	*temp;

	temp = lex->first;
	while (temp)
	{
		if (temp->type == VAR)
			temp->value = expand_var(data, &temp->value[1]);
		if (temp->type == S_QUATE)
			temp->value = expand_s_quote(temp->value);
		temp = temp->next;
	}
}