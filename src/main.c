/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:45:30 by cbitca            #+#    #+#             */
/*   Updated: 2025/06/18 18:03:58 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "env.h"
#include "input.h"
#include <locale.h>
#include <stdio.h>


int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	*test;

	data = ft_calloc(sizeof(t_data), sizeof(t_data));
	parse_env(data, envp);
	// print_env(data->env);
	data->exit_status = 0;
	test = rl_loop(data);
	free(data);
	return (0);
	(void)argc;
	(void)argv;
}

void	print_env(t_env_var *env)
{
	t_env_var *ptr;

	ptr = env;
	while (ptr != NULL)
	{
		printf("%s=", ptr->key);
		printf("%s\n", ptr->value);
		ptr = ptr->next;
	}
}
