/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:45:30 by cbitca            #+#    #+#             */
/*   Updated: 2025/06/11 12:21:31 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_header(void)
{
	printf("\033[1;32m");
	printf("╔════════════════════════════════════════════════════════╗\n");
	printf("║                                                        ║\n");
	printf("║   🐚  Welcome to Minishell v0.42                       ║\n");
	printf("║   ✨  A project by cbitca                              ║\n");
	printf("║                                                        ║\n");
	printf("║                                                        ║\n");
	printf("║                                                        ║\n");
	printf("╚════════════════════════════════════════════════════════╝\n");
	printf("\033[0m");
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	data = ft_calloc(sizeof(t_data), sizeof(t_data));
	data->env = parse_env(data->env, env);
	print_header();
	while (data->env)
	{
		printf("%s : ", data->env->key);
		printf("%s\n", data->env->value);
		data->env = data->env->next;
	}
	return (0);
	(void)argc;
	(void)argv;
}
