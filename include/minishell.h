/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:48:25 by cbitca            #+#    #+#             */
/*   Updated: 2025/05/18 18:48:29 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <termios.h>
# include "../lib/libft/include/libft.h"
# include "../src/env/env.h"
# include "../src/parser/parser.h"

typedef struct s_data
{
	t_env_var	*env;
	char		*line;
	char		*prompt;
}	t_data;

void	cmd_line(t_data *data);

#endif
