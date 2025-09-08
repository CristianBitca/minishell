/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:13:08 by skirwan           #+#    #+#             */
/*   Updated: 2025/08/28 15:31:16 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "expansion.h"

char	*create_here_doc_temp_file_path(int prcs_index, int here_doc_count)
{
	char	*here_doc_number;
	char	*prcs_index_number;
	char	*here_doc_path;
	char	*temp;

	here_doc_number = ft_itoa(here_doc_count);
	prcs_index_number = ft_itoa(prcs_index);
	here_doc_path = ft_strjoin("/tmp/.here_doc", prcs_index_number);
	temp = ft_strjoin(here_doc_path, "_");
	(free(here_doc_path), free(prcs_index_number));
	here_doc_path = ft_strjoin(temp, here_doc_number);
	(free(temp), free(here_doc_number));
	return (here_doc_path);
}

char	*here_doc_readline(t_data *data, int here_doc_fd, char *delimiter, int	*exp_flag)
{
	char	*input;

	input = readline("> ");
	while (!(input && *input))
		input = readline("> ");
	if (ft_strncmp(input, delimiter, ft_strlen(input)) == 0)
		return (delimiter);
	if (input && *input)
	{
		add_history(input);
		input = expand_input(data, input, exp_flag);
		write(here_doc_fd, input, ft_strlen(input));
		write(here_doc_fd, "\n", 1);
		printf("%s\n", input);
	}
	return (input);
}

int	read_here_doc(t_data *data, char *delimiter, char *here_doc_path)
{
	char	*input;
	int		here_doc_fd;
	int		exp_flag;

	here_doc_fd = open(here_doc_path, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (here_doc_fd == -1)
		return (-1);
	delimiter = expand_delimiter(delimiter, &exp_flag);
	printf("%s\n", delimiter);
	input = here_doc_readline(data, here_doc_fd, delimiter, &exp_flag);
	while (input != delimiter)
		input = here_doc_readline(data, here_doc_fd, delimiter, &exp_flag);
	if (close(here_doc_fd) == -1)
		return (-1);
	return (0);
}

int	convert_here_docs(t_data *data, int token_count, int prcs_index)
{
	char	*here_doc_path;
	int		here_doc_count;
	t_token	*traverser;
	
	here_doc_count = 0;
	traverser = data->tokens;
	while (token_count-- > 0)
	{
		if (traverser->type == REDIR_HEREDOC)
		{
			here_doc_path = create_here_doc_temp_file_path(prcs_index, here_doc_count);
			if (read_here_doc(data, traverser->next->value, here_doc_path) == -1)
			{
				(perror(here_doc_path), free(here_doc_path));
				return (-1);
			}
			free(traverser->next->value);
			traverser->next->value = here_doc_path;
			traverser->type = REDIR_IN;
			here_doc_count++;
		}
		traverser = traverser->next;
	}
	return (0);
}
