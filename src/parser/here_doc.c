/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:13:08 by skirwan           #+#    #+#             */
/*   Updated: 2025/09/26 16:08:04 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include "ms_signals.h"
#include "expansion.h"
#include <stdlib.h>
#include <unistd.h>

extern volatile int	g_signal;

char	*create_here_doc_temp_file_path(int prcs_index)
{
	char	*prcs_index_number;
	char	*here_doc_path;

	prcs_index_number = ft_itoa(prcs_index);
	here_doc_path = ft_strjoin("/tmp/.here_doc", prcs_index_number);
	free(prcs_index_number);
	return (here_doc_path);
}

int	here_doc_readline(t_data *data, int here_doc_fd, char *delimiter, int *exp_flag)
{
	char	*input;

	rl_event_hook = &ms_rl_event;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			input = readline("> ");
		else
		{
			char	*line;
			line = ft_get_next_line(STDIN_FILENO);
			input = ft_strtrim(line, "\n");
			free(line);
		}
		if (g_signal == SIGINT)
		{
			rl_replace_line("", 1);
			g_signal = 0;
			return (-1);
		}
		if (input == NULL)
		{
			write(2, "warning: here_doc delimited by end-of-file (wanted `", 53);
			write(2, delimiter, ft_strlen(delimiter));
			write(2, "')\n", 3);
			return (0);
		}
		if (ft_strncmp(input, delimiter, ft_strlen(input)) == 0)
			return (0);
		if (input && *input)
		{
			input = expand_input(data, input, exp_flag);
			write(here_doc_fd, input, ft_strlen(input));
			write(here_doc_fd, "\n", 1);
			free(input);
		}
	}
}

int	read_here_doc(t_data *data, char *delimiter, char *here_doc_path)
{
	int		here_doc_fd;
	int		exp_flag;

	here_doc_fd = open(here_doc_path, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (here_doc_fd == -1)
		return (-1);
	delimiter = expand_delimiter(delimiter, &exp_flag);
	if (here_doc_readline(data, here_doc_fd, delimiter, &exp_flag) == -1)
		return (-2);
	if (close(here_doc_fd) == -1)
		return (-1);
	free(delimiter);
	return (0);
}

int	convert_here_docs(t_data *data, t_token *traverser, int token_count, int prcs_index)
{
	char	*here_doc_path;
	int		read_result;

	while (token_count-- > 0)
	{
		if (traverser->type == REDIR_HEREDOC)
		{
			here_doc_path = create_here_doc_temp_file_path(prcs_index);
			read_result = read_here_doc(data, traverser->next->value, here_doc_path);
			if (read_result == -1)
			{
				(perror(here_doc_path), free(here_doc_path));
				return (-1);
			}
			if (read_result == -2)
			{
				free(here_doc_path);
				return (-2);
			}
			traverser->next->value = here_doc_path;
			traverser->type = REDIR_IN;
		}
		traverser = traverser->next;
	}
	return (0);
}
