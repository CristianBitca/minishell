/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:45:30 by cbitca            #+#    #+#             */
/*   Updated: 2025/06/18 11:55:39 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "env.h"
#include "input.h"


int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	*test;

	data = ft_calloc(sizeof(t_data), sizeof(t_data));
	data->env = parse_env(data->env, envp);
	data->exit_status = 0;
	test = rl_loop(data);
	return (0);
	(void)argc;
	(void)argv;
}
