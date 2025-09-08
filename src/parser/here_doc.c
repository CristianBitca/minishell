/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:13:08 by skirwan           #+#    #+#             */
/*   Updated: 2025/09/03 12:38:50 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

char	*create_here_doc_temp_file_path(int prcs_index)
{
	char	*prcs_index_number;
	char	*here_doc_path;

	prcs_index_number = ft_itoa(prcs_index);
	here_doc_path = ft_strjoin("/tmp/.here_doc", prcs_index_number);
	free(prcs_index_number);
	return (here_doc_path);
}

char	*here_doc_readline(int here_doc_fd, char *delimiter)
{
	char	*input;

	input = readline("> ");
	while (!(input && *input))
		input = readline("> ");
	if (ft_strncmp(input, delimiter, ft_strlen(input)) == 0)
		return (delimiter);
	if (input && *input)
	{
		// input = here_doc_expand_input(input);
		if (ft_strncmp(input, delimiter, ft_strlen(input)) != 0)
		{
			write(here_doc_fd, input, ft_strlen(input));
			write(here_doc_fd, "\n", 1);
		}
	}
	return (input);
}

int	read_here_doc(char *delimiter, char *here_doc_path)
{
	char	*input;
	int		here_doc_fd;
	// int		rule;

	here_doc_fd = open(here_doc_path, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (here_doc_fd == -1)
		return (-1);
	// delimiter = expand_delimiter(delimiter, &rule);
	input = here_doc_readline(here_doc_fd, delimiter);
	while (ft_strncmp(input, delimiter, ft_strlen(input)) != 0)
		input = here_doc_readline(here_doc_fd, delimiter);
	if (close(here_doc_fd) == -1)
		return (-1);
	return (0);
}

int	convert_here_docs(t_token *traverser, int token_count, int prcs_index)
{
	char	*here_doc_path;

	while (token_count-- > 0)
	{
		if (traverser->type == REDIR_HEREDOC)
		{
			here_doc_path = create_here_doc_temp_file_path(prcs_index);
			if (read_here_doc(traverser->next->value, here_doc_path) == -1)
			{
				(perror(here_doc_path), free(here_doc_path));
				return (-1);
			}
			free(traverser->next->value);
			traverser->next->value = here_doc_path;
			traverser->type = REDIR_IN;
		}
		traverser = traverser->next;
	}
	return (0);
}
