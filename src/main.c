/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:45:30 by cbitca            #+#    #+#             */
/*   Updated: 2025/06/30 17:10:59 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "env.h"
#include "execution.h"
#include "input.h"
#include <stdio.h>


int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	**test;

	data = ft_calloc(sizeof(t_data), sizeof(t_data));
	parse_env(data, envp);
	// print_envp(data);
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
}
