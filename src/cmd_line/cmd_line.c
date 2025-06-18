/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:36:41 by cbitca            #+#    #+#             */
/*   Updated: 2025/06/10 18:36:43 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_line.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	cmd_line(t_data *data)
{
	while (1)
	{
		data->line = readline(prompt(data));
		if (data->line && *data->line)
			add_history(data->line);
		parse(data);
	}
}