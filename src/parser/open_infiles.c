/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_infiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:47:13 by skirwan           #+#    #+#             */
/*   Updated: 2025/09/02 13:35:46 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	check_infile_permissions(char *file_path)
{
	if (access(file_path, F_OK) == -1)
	{
		write(STDERR_FILENO, file_path, ft_strlen(file_path));
		write(STDERR_FILENO, ": No such file or directory\n", 29);
		return (-1);
	}
	if (access(file_path, R_OK) == -1)
	{
		write(STDERR_FILENO, file_path, ft_strlen(file_path));
		write(STDERR_FILENO, ": Permission denied\n", 21);
		return (-1);
	}
	return (1);
}

// Counts how many infile redirections there are within this process and
// allocates an int array of that size, to store all the fds which will
// return when we open the infiles.
int	*create_infilefds_array(t_token *traverser, int token_count)
{
	int	*fds;
	int	infile_count;

	infile_count = 0;
	while (token_count-- > 0 && traverser != NULL)
	{
		if (traverser->type == REDIR_IN)
			infile_count++;
		traverser = traverser->next;
	}
	fds = malloc(infile_count * sizeof(*fds));
	return (fds);
}

int	open_infile(int *fds, int fd_index, char *file_path)
{
	int	infilefd;

	infilefd = open(file_path, O_RDONLY);
	if (infilefd == -1)
	{
		perror(file_path);
		return (-1);
	}
	fds[fd_index] = infilefd;
	return (1);
}

// If we have multiple infile redirections, we only need to keep the last fd
// in the token chain open, so we close all other fds up to that point.
// Also if either access or open fails for an infile, we must close all open
// fds up to that point.
int	close_redundant_fds(int **fds, int fds_to_close)
{
	int	*fd_array;

	fd_array = *fds;
	if (fds_to_close < 0)
	{
		free(fd_array);
		return (-1);
	}
	while (fds_to_close >= 0)
	{
		if (close(fd_array[fds_to_close] == -1))
		{
			free(fd_array);
			return (-1);
		}
		fds_to_close--;
	}
	free(fd_array);
	return (-1);
}

int	handle_infiles(t_token *traverser, int token_count)
{
	int		*fds;
	int		fd_index;
	int		infile;

	fd_index = 0;
	fds = create_infilefds_array(traverser, token_count);
	while (token_count-- > 0)
	{
		if (traverser->type == REDIR_IN)
		{
			if (check_infile_permissions(traverser->next->value) == -1)
				return (close_redundant_fds(&fds, fd_index - 1));
			if (open_infile(fds, fd_index, traverser->next->value) == -1)
				return (close_redundant_fds(&fds, fd_index - 1));
			fd_index++;
		}
		traverser = traverser->next;
	}
	if (fd_index != 0)
		infile = fds[fd_index - 1];
	else
		infile = STDIN_FILENO;
	close_redundant_fds(&fds, fd_index - 2);
	return (infile);
}
