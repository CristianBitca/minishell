/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:45:30 by cbitca            #+#    #+#             */
/*   Updated: 2025/05/18 18:45:32 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>
#include <readline/readline.h>

void	print_header(void)
{
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
}
