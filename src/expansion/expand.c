/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 12:15:34 by skirwan           #+#    #+#             */
/*   Updated: 2025/08/08 16:08:58 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"

void	check_to_expand(t_data *data, t_token *token)
{
	char	*word;
	int		i;

	word = token->value;
	i = 0;
	while (word[i] != '\0')
	{
		if (word[i] == '$')
			expand_env(data, token, i);
	}
}

void	expand(t_data *data)
{
	t_token	*temp;

	temp = data->tokens;
	while (temp->next != NULL)
	{
		if (temp->type == WORD)
			check_to_expand(data, temp);
		temp = temp->next;
	}
}
