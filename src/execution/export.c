/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:23:42 by skirwan           #+#    #+#             */
/*   Updated: 2025/06/30 17:11:40 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "execution.h"
#include "env.h"

// mimics behaviour of export with no options or arguments
void	print_export(t_data *data)
{
	t_env_var	*env_var;
	char		*to_print;
	char		*buf;

	env_var = data->env;
	while (env_var != NULL)
	{
		to_print = ft_strjoin("declare -x ", env_var->key);
		if (env_var->value != NULL)
		{
			buf = to_print;
			to_print = ft_strjoin(to_print, "=\"");
			free(buf);
			buf = to_print;
			to_print = ft_strjoin(to_print, env_var->value);
			free(buf);
			buf = to_print;
			to_print = ft_strjoin(to_print, "\"");
			free(buf);
		}
		ft_printf("%s\n", to_print);
		free(to_print);
		env_var = env_var->next;
	}
}

// checks if variable exported has a value for the key by finding '='
int	find_equality(char	*str)
{
	while (*str)
	{
		if (*str == '=')
			return (1);
		str++;
	}
	return (0);
}

// if the variable exported has no value, key is appended with NULL to allow it to be found for
// export with no options or arguments. Otherwise adds key and value to our environment
// representation
void	export(t_data *data, char **args)
{
	char		*key;
	char		*value;
	int			i;

	if (args == NULL)
	{
		print_export(data);
		return ;
	}
	while (*args)
	{
		i = 0;
		if (find_equality(*args) == 0)
		{
			key = ft_strdup(*args);
			append_stack(&data->env, new_node(key, NULL));
			args++;
			continue ;
		}
		while ((*args)[i] != '=')
			i++;
		key = ft_substr(*args, 0, i);
		value = ft_strdup(&((*args)[i + 1]));
		append_stack(&data->env, new_node(key, value));
		args++;
	}
}
