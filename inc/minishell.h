/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:48:25 by cbitca            #+#    #+#             */
/*   Updated: 2025/06/11 12:00:43 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../inc/libft.h"
# include "../src/env/env.h"

typedef struct s_data
{
	t_env_var	*env;
}	t_data;

typedef struct s_cmd_data
{
	char	**argv;
	char	**envp;
	int	infilefd;
	int	outfilefd;
} t_cmd_data;

#endif
