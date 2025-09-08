/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_s_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:26:38 by cbitca            #+#    #+#             */
/*   Updated: 2025/08/19 20:26:40 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"

char	*expand_s_quote(char *input, t_expand *exp)
{
	char	*new_word;

	exp->expand = ft_substr(exp->expand, 1, exp->l_expand - 2);
	exp->l_expand = ft_strlen(exp->expand);
	new_word = ft_strjoin(exp->before, exp->expand);
	new_word = ft_strjoin(new_word, exp->after);
	exp->pos = exp->l_before + exp->l_expand;
	exp->size = ft_strlen(new_word);
	return (new_word);
	(void)input;
}

char	*expand_d_quote(char *input, t_expand *exp)
{
	char	*new_word;

	exp->expand = ft_substr(exp->expand, 1, exp->l_expand - 2);
	exp->l_expand = ft_strlen(exp->expand);
	new_word = ft_strjoin(exp->before, exp->expand);
	new_word = ft_strjoin(new_word, exp->after);
	exp->pos = exp->l_before;
	exp->size = ft_strlen(new_word);
	return (new_word);
	(void)input;
}
