/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_infiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:47:13 by skirwan           #+#    #+#             */
/*   Updated: 2025/08/28 15:33:10 by skirwan          ###   ########.fr       */
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
// allocates an int array of that size plus one.
// The last element in the array is set to -42 as a terminator.
// Using -42 is possible because successful calls to open() will always return
// a positive number for the fd, or will be -1 on error which we will catch.
int	*create_infilefds_array(t_token *traverser, int token_count)
{
	int	*fds;
	int	infile_count;

	infile_count = 0;
	while (token_count-- > 0)
	{
		if (traverser->type == REDIR_IN)
			infile_count++;
		traverser = traverser->next;
	}
	fds = malloc((infile_count + 1) * sizeof(*fds));
	fds[infile_count] = -42;
	return (fds);
}

int	open_infile(int *fds, int fd_index, char *file_path)
{
	int	infilefd;

	infilefd = open(file_path, O_RDONLY);
	if (infilefd == -1)
	{
		perror(NULL);
		return (-1);
	}
	fds[fd_index] = infilefd;
	return (1);
}

// If we have multiple infile redirections, we only need to keep the last fd
// in the token chain open, so we close all other fds up to that point.
// Also if either access or open fails for an infile, we must close all open
// fds up to that point.
int	close_infilefds(int **fds, int fds_index)
{
	int	*fd_array;

	fd_array = *fds;
	if (fds_index < 0)
	{
		free(fd_array);
		return (1);
	}
	while (fds_index >= 0)
	{
		if (close(fd_array[fds_index] == -1))
		{
			free(fd_array);
			return (-1);
		}
		fds_index--;
	}
	free(fd_array);
	return (-1);
}

int	handle_infiles(t_token *traverser, int token_count, int read_pipe_fd)
{
	char	*file_path;
	int		*fds;
	int		fd_index;
	int		infile;

	fd_index = 0;
	fds = create_infilefds_array(traverser, token_count);
	while (token_count-- > 0)
	{
		if (traverser->type == REDIR_IN)
		{
			file_path = traverser->next->value;
			if (check_infile_permissions(file_path) == -1)
				return (close_infilefds(&fds, fd_index - 1));
			if (open_infile(fds, fd_index, file_path) == -1)
				return (close_infilefds(&fds, fd_index - 1));
			fd_index++;
		}
		traverser = traverser->next;
	}
	if (fd_index == 0 && !read_pipe_fd)
		infile = STDIN_FILENO;
	else if (fd_index != 0)
		infile = fds[fd_index - 1];
	else
		infile = read_pipe_fd;
	close_infilefds(&fds, fd_index - 2);
	return (infile);
}
