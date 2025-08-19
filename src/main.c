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

<<<<<<< HEAD
#include "../include/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
=======
#include "libft.h"
#include "minishell.h"
#include "env.h"
#include "input.h"
>>>>>>> skirwan

void	test_env(t_data *data)
{
<<<<<<< HEAD
	printf("\033[1;32m");
	printf("╔════════════════════════════════════════════════════════╗\n");
	printf("║                                                        ║\n");
	printf("║   🐚  Welcome to Minishell v0.42                       ║\n");
	printf("║   ✨  A project by cbitca and skirwan                  ║\n");
	printf("║                                                        ║\n");
	printf("║                                                        ║\n");
	printf("║                                                        ║\n");
	printf("╚════════════════════════════════════════════════════════╝\n");
	printf("\033[0m");
}

t_data	*init_data(t_data *data, char **env)
{
	data->env = parse_env(data->env, env);
	return (data);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	data = ft_calloc(sizeof(t_data), sizeof(t_data));
	data = init_data(data, env);
	print_header();
	while (1)
	{
		cmd_line(data);
	}
	return (0);
=======
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
	(void)argc;
	(void)argv;
	(void)envp;
>>>>>>> skirwan
}
