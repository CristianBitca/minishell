/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_outfiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:44:00 by skirwan           #+#    #+#             */
/*   Updated: 2025/09/02 13:36:35 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	*create_outfilefds_array(t_token *traverser, int token_count)
{
	int	*fds;
	int	outfile_count;

	outfile_count = 0;
	while (token_count-- > 0)
	{
		if (traverser->type == REDIR_OUT || traverser->type == REDIR_APPEND)
			outfile_count++;
		traverser = traverser->next;
	}
	fds = malloc(outfile_count * sizeof(*fds));
	return (fds);
}

int	check_outfile_permissions(char *file_path)
{
	if (access(file_path, F_OK) == 0)
	{
		if (access(file_path, W_OK) == -1)
		{
			write(STDERR_FILENO, file_path, ft_strlen(file_path));
			write(STDERR_FILENO, ": Permission denied\n", 21);
			return (-1);
		}
	}
	return (1);
}

int	open_outfile(int *fds, int fd_index, char *file_path, int type)
{
	int	outfilefd;

	if (type == REDIR_APPEND)
		outfilefd = open(file_path, O_APPEND | O_CREAT | O_RDWR, 0644);
	if (type == REDIR_OUT)
		outfilefd = open(file_path, O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (outfilefd == -1)
	{
		perror(file_path);
		return (-1);
	}
	fds[fd_index] = outfilefd;
	return (1);
}

int	handle_outfiles(t_token *traverser, int token_count)
{
	int		*fds;
	int		fd_index;
	int		outfile;

	fd_index = 0;
	fds = create_outfilefds_array(traverser, token_count);
	while (token_count-- > 0 && traverser != NULL)
	{
		if (traverser->type == REDIR_OUT || traverser->type == REDIR_APPEND)
		{
			if (check_outfile_permissions(traverser->next->value) == -1)
				return (close_redundant_fds(&fds, fd_index - 1));
			if (open_outfile(fds, fd_index, traverser->next->value, traverser->type) == -1)
				return (close_redundant_fds(&fds, fd_index - 1));
			fd_index++;
		}
		traverser = traverser->next;
	}
	if (fd_index != 0)
		outfile = fds[fd_index - 1];
	else
		outfile = STDOUT_FILENO;
	close_redundant_fds(&fds, fd_index - 2);
	return (outfile);
}
