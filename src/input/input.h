/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:56:30 by skirwan           #+#    #+#             */
/*   Updated: 2025/06/18 11:56:46 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <unistd.h>

char	*rl_loop(t_data *data);
char	*create_prompt(t_data *data);
void	input_to_cmd(t_data *data, char *input);

#endif
