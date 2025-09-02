/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:51:47 by skirwan           #+#    #+#             */
/*   Updated: 2025/09/02 17:22:04 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int		count_arguments(t_token *traverser, int token_count)
{
	int	arg_count;

	arg_count = 0;
	while (token_count-- > 0 && traverser != NULL)
	{
		if (traverser->type == WORD)
		{
			if (traverser->prev != NULL &&
				(traverser->prev->type == WORD || traverser->prev->type == PIPE))
				arg_count++;
		}
		traverser = traverser->next;
	}
	return (arg_count);
}

int		check_valid_command(char *cmd)
{
	struct stat	file_status;

	if (access(cmd, F_OK) == 0)
	{
		if (stat(cmd, &file_status) == -1)
		{
			perror(cmd);
			return (-1);
		}
		if (file_status.st_mode & S_IFDIR)
		{
			write(STDERR_FILENO, cmd, ft_strlen(cmd));
			write(STDERR_FILENO, ": Is a directory\n", 18);
			return (-1);
		}
		if (access(cmd, X_OK) == 0)
			return (0);
		write (STDERR_FILENO, cmd, ft_strlen(cmd));
		write (STDERR_FILENO, ": Permission denied\n", 22);
		return (-1);
	}
	return (0);
}

char	*create_command(char *cmd)
{
	if (check_valid_command(cmd) == -1)
		return (NULL);
	return (cmd);
}

char	**make_process_argv(t_token *traverser, int token_count)
{
	char	**argv;
	int		arg_count;

	arg_count = count_arguments(traverser, token_count);
	argv = malloc(arg_count * sizeof(*argv));
	
	return (argv);
}
