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

void	expand_exit_code(t_data *data, t_token *token, char *expand_ptr)
{
	char	*exit_code;
	char	*new_word;
	char	*post_var;
	char	*pre_var;
	char	*temp;

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
}

// Checks
void	expand_env(t_data *data, t_token *token, char *expand_ptr)
{
	char	*remainder;
	char	*to_expand;
	int		i;

	i = 1;
	if (expand_ptr[i] == '?')
		return (expand_exit_code(data, token, expand_ptr));
	if (expand_ptr[i] == '"' || expand_ptr[i] == '\'')
		return (invalid_env_expansion(token, expand_ptr, 1));
	if (ft_isalpha(expand_ptr[i]) == 0 && expand_ptr[i] != '_')
		return (invalid_env_expansion(token, expand_ptr, 2));
	while (expand_ptr[i] != '\0' && expand_ptr[i] != '$'
		&& expand_ptr[i] != '"' && expand_ptr[i] != '\''
		&& (ft_isalnum(expand_ptr[i]) == 1 || expand_ptr[i] == '_'))
		i++;
	to_expand = ft_substr(expand_ptr, 1, i);
	if (find_env(data->env, to_expand) == NULL)
	{
		invalid_env_expansion(token, expand_ptr, i);
		free(to_expand);
		return ;
	}
	remainder = ft_strdup(expand_ptr + i);
	valid_env_expand(data, token, to_expand, remainder);
}
