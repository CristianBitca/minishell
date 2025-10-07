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
#include "env.h"

int	count_env(char *input)
{
	int	i;

	i = 0;
	while (*input)
	{
		if (*input == '$')
			i++;
		input++;
	}
	return (i);
}

char	*insert_env(t_data *data, char *input)
{
	t_expand	*exp;
	char		*temp;
	char		*new_word;

	exp = ft_calloc(sizeof(t_expand), 1);
	exp->size = ft_strlen(input);
	while (input[exp->pos] != '$' && input[exp->pos + 1])
		exp->pos++;
	split_expand(input, exp);
	temp = exp->expand;
	if (exp->expand[1] == ' ' || !exp->expand[1])
		exp->expand = ft_strdup(exp->expand);
	else if (exp->expand[1] == '?')
		exp->expand = ft_itoa(data->exit_status);
	else if (!find_env(data->env, &exp->expand[1]))
		exp->expand = ft_strdup("");
	else
		exp->expand = ft_strdup(find_env(data->env, &exp->expand[1]));
	free(temp);
	exp->l_expand = ft_strlen(exp->expand);
	new_word = ft_strjoin(exp->before, exp->expand);
	temp = new_word;
	new_word = ft_strjoin(new_word, exp->after);
	(free(temp), free_exp_value(exp), free(exp));
	return (new_word);
}

char	*expand_s_quote(t_token *token, t_expand *exp)
{
	char	*new_word;
	char	*temp;

	temp = exp->expand;
	exp->expand = ft_substr(exp->expand, 1, exp->l_expand - 2);
	free(temp);
	exp->l_expand = ft_strlen(exp->expand);
	new_word = ft_strjoin(exp->before, exp->expand);
	temp = new_word;
	new_word = ft_strjoin(new_word, exp->after);
	free(temp);
	exp->pos = exp->l_before + exp->l_expand;
	exp->size = ft_strlen(new_word);
	if (token)
		free(token->value);
	free_exp_value(exp);
	return (new_word);
}

char	*expand_d_quote(t_data *data, t_token *token, t_expand *exp)
{
	char	*new_word;
	char	*temp;
	int		count;

	temp = exp->expand;
	exp->expand = ft_substr(exp->expand, 1, exp->l_expand - 2);
	free(temp);
	count = count_env(exp->expand);
	while (count)
	{
		temp = exp->expand;
		exp->expand = insert_env(data, exp->expand);
		free(temp);
		count--;
	}
	exp->l_expand = ft_strlen(exp->expand);
	new_word = ft_strjoin(exp->before, exp->expand);
	temp = new_word;
	new_word = ft_strjoin(new_word, exp->after);
	free(temp);
	exp->pos = exp->l_before + exp->l_expand;
	exp->size = ft_strlen(new_word);
	(free(token->value), free_exp_value(exp));
	return (new_word);
}
