/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:40:36 by skirwan           #+#    #+#             */
/*   Updated: 2025/06/18 15:51:30 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

char	**join_key_val(t_data *data)
{
	t_env_var	*env_value;
	char	**envp;
	int	i;

	env_value = data->env;
	i = 0;
	while (env_value != NULL)
	{
		env_value = env_value->next;
		i++;
	}
	envp = malloc(sizeof(*envp) * i);
	return (envp);
}
