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

char	*expand_s_quote(t_expand *exp)
{
	char	*new_word;
	char	*temp;

	exp->expand = ft_substr(exp->expand, 1, exp->l_expand - 2);
	exp->l_expand = ft_strlen(exp->expand);
	new_word = ft_strjoin(exp->before, exp->expand);
	temp = new_word;
	new_word = ft_strjoin(new_word, exp->after);
	free(temp);
	exp->pos = exp->l_before + exp->l_expand;
	exp->size = ft_strlen(new_word);
	free_exp_value(exp);
	return (new_word);
}

char	*expand_d_quote(t_expand *exp)
{
	char	*new_word;
	char	*temp;

	exp->expand = ft_substr(exp->expand, 1, exp->l_expand - 2);
	exp->l_expand = ft_strlen(exp->expand);
	new_word = ft_strjoin(exp->before, exp->expand);
	temp = new_word;
	new_word = ft_strjoin(new_word, exp->after);
	free(temp);
	exp->pos = exp->l_before;
	exp->size = ft_strlen(new_word);
	free_exp_value(exp);
	return (new_word);
}
