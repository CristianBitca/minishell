/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:23:42 by skirwan           #+#    #+#             */
/*   Updated: 2025/09/12 12:21:11 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "built_in.h"
#include "env.h"

// Mimics behaviour of export with no options or arguments. Simply writes
// out every exported variable, including internal variables.
void	print_export(t_data *data, int out_fd)
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
		write (out_fd, to_print, ft_strlen(to_print));
		write (out_fd, "\n", 1);
		free(to_print);
		env_var = env_var->next;
	}
}

// If export argument has no '=', if the key to export already exits,
// it is not changed, else key added to env list with value NULL
// to be found for export with no options or arguments
void	export_without_value(t_data *data, char *to_export)
{
	char	*key;

	if (find_env(data->env, to_export) != NULL)
		return ;
	key = ft_strdup(to_export);
	append_stack(&data->env, new_node(key, NULL));
}

// If key to be exported is already part of the env, value of the node
// already present is changed to prevent duplicating keys, else key is
// appended to env list with the value. We substr and strdup to make
// new memory allocated strings for consistency, as every key, value
// in the env list will be memory allocated.
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

// The first character in an environment variable must either be
// alphabetic or an '_'. If the first character is an underscore
// another valid alphanumeric character must follow, an environment
// variable key cannot only contain an '_'. Following the first character
// and before the '=' every character must be alphanumeric or an '_'.
int	check_valid_export(t_data *data, char *to_export)
{
	int	i;

	i = 1;
	if (to_export[0] == '_' && (to_export[1] == '\0'
			|| to_export[1] == '='))
		return (0);
	if (ft_isalpha(to_export[0]) == 0 && to_export[0] != '_')
	{
		invalid_export_identifier(data, to_export);
		return (0);
	}
	while (to_export[i] && to_export[i] != '=')
	{
		if (ft_isalnum(to_export[i]) == 0 && to_export[i] != '_')
		{
			invalid_export_identifier(data, to_export);
			return (0);
		}
		i++;
	}
	return (1);
}

// If the variable exported has no '=', key is appended with NULL value
// to allow it to be found for export with no options or arguments.
// Otherwise adds key and value to env list
void	export(t_data *data, char **args, int out_fd)
{
	args++;
	if (*args == NULL)
	{
		print_export(data, out_fd);
		data->exit_status = EXIT_SUCCESS;
		return ;
	}
	data->exit_status = EXIT_SUCCESS;
	while (*args)
	{
		if (check_valid_export(data, *args) == 0)
			data->exit_status = EXIT_FAILURE;
		else if (ft_strchr(*args, '=') == 0)
			export_without_value(data, *args);
		else
			export_with_value(data, *args);
		args++;
	}
}
