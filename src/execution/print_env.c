/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:40:36 by skirwan           #+#    #+#             */
/*   Updated: 2025/06/18 18:27:03 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

char	**join_key_val(t_data *data)
{
	t_env_var	*env;
	char	**envp;
	int	i;

	env = data->env;
	i = 0;
	while (env != NULL)
	{
		env = env->next;
		i++;
	}
	envp = malloc(sizeof(*envp) * i);
	return (envp);
}
