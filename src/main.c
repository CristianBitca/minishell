/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:45:30 by cbitca            #+#    #+#             */
/*   Updated: 2025/09/17 12:58:32 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "minishell.h"
#include "env.h"
#include "input.h"

volatile int	g_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = ft_calloc(sizeof(t_data), sizeof(t_data));
	parse_env(data, envp);
	rl_loop(data);
	full_exit(data, -4242);
	return (0);
	(void)argc;
	(void)argv;
	(void)envp;
}
