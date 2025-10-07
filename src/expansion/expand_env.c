/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:01:14 by skirwan           #+#    #+#             */
/*   Updated: 2025/08/19 14:37:37 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "env.h"
#include "expansion.h"

void	check_qmark(t_expand *exp)
{
	char	*temp;

	if (exp->expand[ft_strlen(exp->expand) - 1] == '?')
	{
		temp = exp->expand;
		exp->expand = ft_substr(exp->expand, 0, ft_strlen(exp->expand) - 1);
		free(temp);
		temp = exp->after;
		exp->after = ft_strjoin("?", exp->after);
		free(temp);
	}
}

// When an invalid char follows $ (any which is not alphabetic or an '_'
// or a '?'), or when the string following the $ is not found in the
// environment. We remove the invalid env variable, by getting the string
// before the invalid variable through substr, then moving the pointer to the
// invalid variable beyond the expansion, and joining whatever is subsequent
// to the string before the invalid variable.
char	*invalid_env_expansion(t_token *token, t_expand *exp)
{
	char	*new_word;
	char	*temp;

	temp = exp->expand;
	exp->expand = ft_strdup("");
	free(temp);
	exp->l_expand = ft_strlen(exp->expand);
	new_word = ft_strjoin(exp->before, exp->expand);
	temp = new_word;
	new_word = ft_strjoin(new_word, exp->after);
	free(temp);
	if (token != NULL)
		free(token->value);
	exp->pos = exp->l_before + exp->l_expand;
	exp->size = ft_strlen(new_word);
	free_exp_value(exp);
	return (new_word);
}

char	*slash_env_expansion(t_token *token, t_expand *exp)
{
	char	*new_word;
	char	*temp;

	temp = exp->expand;
	exp->expand = ft_strdup("$");
	free(temp);
	exp->l_expand = ft_strlen(exp->expand);
	new_word = ft_strjoin(exp->before, exp->expand);
	temp = new_word;
	new_word = ft_strjoin(new_word, exp->after);
	free(temp);
	if (token != NULL)
		free(token->value);
	exp->pos = exp->l_before + exp->l_expand;
	exp->size = ft_strlen(new_word);
	free_exp_value(exp);
	return (new_word);
}

char	*expand_exit_code(t_data *data, t_token *token, t_expand *exp)
{
	char	*new_word;
	char	*temp;

	temp = exp->expand;
	exp->expand = ft_itoa(data->exit_status);
	free(temp);
	exp->l_expand = ft_strlen(exp->expand);
	new_word = ft_strjoin(exp->before, exp->expand);
	temp = new_word;
	new_word = ft_strjoin(new_word, exp->after);
	free(temp);
	if (token != NULL)
		free(token->value);
	exp->pos = exp->l_before + exp->l_expand;
	exp->size = ft_strlen(new_word);
	free_exp_value(exp);
	return (new_word);
}

// Checks
char	*expand_env(t_data *data, t_token *token, t_expand *exp)
{
	char	*new_word;
	char	*temp;

	if (exp->expand[1] == '?')
		return (expand_exit_code(data, token, exp));
	check_qmark(exp);
	if (!ft_strncmp(exp->expand, "$", 2) && ft_strchr(exp->after, '/'))
		return (slash_env_expansion(token, exp));
	if (!find_env(data->env, &exp->expand[1]))
		return (invalid_env_expansion(token, exp));
	temp = exp->expand;
	exp->expand = ft_strdup(find_env(data->env, &exp->expand[1]));
	free(temp);
	if (ft_strchr(exp->expand, ' '))
		return (split_word(data, token, exp, exp->expand));
	exp->l_expand = ft_strlen(exp->expand);
	new_word = ft_strjoin(exp->before, exp->expand);
	temp = new_word;
	new_word = ft_strjoin(new_word, exp->after);
	exp->pos = exp->l_before + exp->l_expand;
	exp->size = ft_strlen(new_word);
	(free(temp), free_exp_value(exp));
	if (token != NULL)
		free(token->value);
	return (new_word);
}
