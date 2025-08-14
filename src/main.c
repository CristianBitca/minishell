/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:45:30 by cbitca            #+#    #+#             */
/*   Updated: 2025/08/04 12:19:51 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "env.h"
#include "built_in.h"
#include "input.h"

void	test_env(t_data *data)
{
	t_env_var *node;

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

	data = ft_calloc(sizeof(t_data), sizeof(t_data));
	parse_env(data, envp);
	// test_env(data);
	rl_loop(data);
	// print_envp(data, 1);
	// export(data, NULL);
	// export(data, test);
	// print_envp(data);
	// data->exit_status = 0;
	// test = rl_loop(data);
	free(data);
	return (0);
	// (void)test;
	(void)argc;
	(void)argv;
	(void)envp;
}
