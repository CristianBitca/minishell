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

// When an invalid char follows $ (any which is not alphabetic or an '_'
// or a '?'), or when the string following the $ is not found in the
// environment. We remove the invalid env variable, by getting the string
// before the invalid variable through substr, then moving the pointer to the
// invalid variable beyond the expansion, and joining whatever is subsequent
// to the string before the invalid variable.
char	*invalid_env_expansion(char *input, t_expand *exp)
{
	char	*new_word;

	exp->expand = ft_strdup("");
	exp->l_expand = ft_strlen(exp->expand);
	new_word = ft_strjoin(exp->before, exp->expand);
	new_word = ft_strjoin(new_word, exp->after);
	exp->pos = exp->l_before + exp->l_expand;
	exp->size = ft_strlen(new_word);
	return (new_word);
	(void)input;
}

char	*expand_exit_code(t_data *data, char *input, t_expand *exp)
{
	char	*new_word;

<<<<<<< HEAD
	exp->expand = ft_itoa(data->exit_status);
	exp->l_expand = ft_strlen(exp->expand);
	new_word = ft_strjoin(exp->before, exp->expand);
	new_word = ft_strjoin(new_word, exp->after);
	exp->pos = exp->l_before + exp->l_expand;
	exp->size = ft_strlen(new_word);
	return (new_word);
	(void)input;
=======
	exit_code = ft_itoa(data->exit_status);
	pre_var = ft_substr(token->value, 0, expand_ptr - token->value);
	temp = ft_strjoin(pre_var, exit_code);
	post_var = expand_ptr + 2;
	new_word = ft_strjoin(temp, post_var);
	(free(temp), free(pre_var), free(exit_code), free(token->value));
	token->value = new_word;
}

void	valid_env_expand(t_data *data, t_token *token, char *key, char *remainder)
{
	char	*expand_value;
	char	*pre_expand;
	int		og_length;
	int		dlr_index;

	og_length = ft_strlen(token->value) + 1;
	dlr_index = ft_strnstr(token->value, key, og_length) - token->value;
	pre_expand = ft_substr(token->value, 0, (dlr_index - 1));
	expand_value = find_env(data->env, key);
	(free(token->value), free(key));
	token->value = pre_expand;
	split_word(token, expand_value, remainder);
>>>>>>> skirwan
}

// Checks
char	*expand_env(t_data *data, t_token *token, char *input, t_expand *exp)
{
	int		i;
	char	*new_word;

	i = 1;
	if (exp->expand[i] == '?')
		return (expand_exit_code(data, input, exp));
	if (!find_env(data->env, &exp->expand[1]))
		return (invalid_env_expansion(input, exp));
	exp->expand = find_env(data->env, &exp->expand[1]);
	exp->l_expand = ft_strlen(exp->expand);
	new_word = ft_strjoin(exp->before, exp->expand);
	new_word = ft_strjoin(new_word, exp->after);
	exp->pos = exp->l_before + exp->l_expand;
	exp->size = ft_strlen(new_word);
	if (ft_strchr(new_word, ' ') && !exp->exp_heredoc)
		split_word(data, token, new_word);
	return (new_word);
}
