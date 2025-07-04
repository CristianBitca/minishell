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

// if export argument has no '=', if the key to export already exits,
// it is not changed, else key added to env list to be found
// for export with no options or arguments
void	export_without_value(t_data *data, char *to_export)
{
	char	*key;

	if (find_env(data->env, to_export) != NULL)
		return ;
	key = ft_strdup(to_export);
	append_stack(&data->env, new_node(key, NULL));
}

// if key to be exported is already part of the env, value of that node
// is changed to prevent duplicating keys, else key is appended to 
// env list with the value
void	export_with_value(t_data *data, char *to_export)
{
	t_env_var	*env_var;
	char		*key;
	char		*value;
	int			i;

	i = 0;
	while ((to_export[i] != '=') && to_export[i])
		i++;
	key = ft_substr(to_export, 0, i);
	value = ft_strdup(&(to_export[i + 1]));
	if (find_env(data->env, key) != NULL)
	{
		env_var = find_env_node(data->env, key);
		(free(env_var->value), free(key));
		env_var->value = value;
	}
	else
		append_stack(&data->env, new_node(key, value));
}

// if the variable exported has no value, key is appended with NULL
// to allow it to be found for export with no options or arguments.
// Otherwise adds key and value to env list
void	export(t_data *data, char **args)
{
	if (args == NULL)
	{
		print_export(data);
		return ;
	}
	while (*args)
	{
		if (find_equality(*args) == 0)
			export_without_value(data, *args);
		else
			export_with_value(data, *args);
		args++;
	}
}
