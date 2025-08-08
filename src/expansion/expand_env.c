/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:01:14 by skirwan           #+#    #+#             */
/*   Updated: 2025/08/08 17:38:34 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "expansion.h"

// When an invalid char follows $ (any which is not alphabetic or an '_'
// or a '?'), or when the string following the $ is not found in the
// environment. We remove the invalid env variable, by getting the string
// before the invalid variable through substr, then moving the pointer to the
// invalid variable beyond the expansion, and joining whatever is subsequent
// to the string before the invalid variable.
void	invalid_env_expansion(t_token *token, char *invalid_var, int var_size)
{
	char	*pre_var;
	char	*new_word;

	pre_var = ft_substr(token->value, 0, invalid_var - token->value);
	while (var_size-- > 0)
		invalid_var++;
	new_word = ft_strjoin(pre_var, invalid_var);
	(free(pre_var), free(token->value));
	token->value = new_word;
}

void	expand_exit_code(t_data *data, t_token *token, char *expand_location)
{
	char	*exit_code;
	char	*new_word;
	char	*pre_var;

	exit_code = ft_itoa(data->exit_status);
	pre_var = ft_substr(token->value, 0, expand_location - token->value);
	new_word = ft_strjoin(pre_var, exit_code);
	
}

// Checks
void	expand_env(t_data *data, t_token *token, int start)
{
	char	*var_substr;
	char	*to_expand;
	int		i;

	var_substr = &token->value[start];
	i = start;
	i++;
	if (var_substr[i] == '?')
	{
		expand_exit_code(data, token, &var_substr[i]);
		return ;
	}
	if (ft_isalpha(var_substr[i]) == 0 && var_substr[i] != '_')
	{
		to_expand = var_substr;
		invalid_env_expansion(token, to_expand, (i - start) + 1);
		return ;
	}
	while (var_substr[i] != '\0')
	{
		
	}
}
