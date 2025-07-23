/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_line.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:43:45 by cbitca            #+#    #+#             */
/*   Updated: 2025/06/10 18:43:46 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_LINE_H
# define CMD_LINE_H

# include "../../include/minishell.h"

typedef struct s_data	t_data;

char	*prompt(t_data *data);
void	parse(t_data *data);

#endif
