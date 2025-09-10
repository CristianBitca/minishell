/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:45:30 by cbitca            #+#    #+#             */
/*   Updated: 2025/09/10 12:05:12 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "minishell.h"
#include "env.h"
#include "input.h"

void	test_env(t_data *data)
{
	t_env_var	*node;

	node = data->env;
	while (node != NULL)
	{
		printf("key = %s\n", node->key);
		printf("value = %s\n", node->value);
		printf("\n");
		node = node->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	if (isatty(STDIN_FILENO) == 0)
		return (0);
	data = ft_calloc(sizeof(t_data), sizeof(t_data));
	parse_env(data, envp);
	rl_loop(data);
	full_exit(data);
	return (0);
	(void)argc;
	(void)argv;
	(void)envp;
}
