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
void	invalid_env_expansion(t_token *token, char *expand_ptr, int var_size)
{
	char	*post_var;
	char	*pre_var;
	char	*new_word;

	pre_var = ft_substr(token->value, 0, expand_ptr - token->value);
	post_var = expand_ptr;
	while (var_size-- > 0)
		post_var++;
	new_word = ft_strjoin(pre_var, post_var);
	(free(pre_var), free(token->value));
	token->value = new_word;
}

void	expand_exit_code(t_data *data, t_token *token, t_expand *exp)
{
	char	*new_word;

	exp->expand = ft_itoa(data->exit_status);
	new_word = ft_strjoin(exp->before, exp->expand);
	new_word = ft_strjoin(new_word, exp->before);
	token->value = new_word;
	printf("%s\n", token->value);
}

void	valid_env_expand(t_data *data, t_token *token, char *key, char *remainder)
{
	char	*expand_value;
	char	*pre_expand;
	int		og_length;
	int		$_index;

	og_length = ft_strlen(token->value) + 1;
	$_index = ft_strnstr(token->value, key, og_length) - token->value;
	pre_expand = ft_substr(token->value, 0, ($_index - 1));
	expand_value = find_env(data->env, key);
	(free(token->value));
	token->value = pre_expand;
	printf("%s \n", expand_value);
	split_word(token, expand_value, remainder);
}

// Checks
void	expand_env(t_data *data, t_token *token, t_expand *exp)
{
	int	i;

	i = 1;
	if (exp->expand[i] == '?')
		return (expand_exit_code(data, token, exp));
	if (exp->expand[i] == '"' || exp->expand[i] == '\'')
		return (invalid_env_expansion(token, &exp->expand[i], 1));
	if (ft_isalpha(exp->expand[i]) == 0 && exp->expand[i] != '_')
		return (invalid_env_expansion(token, &exp->expand[i], 2));
	while (exp->expand[i] && exp->expand[i] != '$'
		&& exp->expand[i] != '"' && exp->expand[i] != '\''
		&& (ft_isalnum(exp->expand[i]) == 1 || exp->expand[i] == '_'))
		i++;
	if (find_env(data->env, &exp->expand[1]) == NULL)
	{
		invalid_env_expansion(token, exp->expand, exp->pos);
		return ;
	}
	printf("to expand %s : \n remainder %s: \n", &exp->expand[1], exp->after);
	valid_env_expand(data, token, &exp->expand[1], exp->after);
}
