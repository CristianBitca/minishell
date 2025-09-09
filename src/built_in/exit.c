/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:09:46 by skirwan           #+#    #+#             */
/*   Updated: 2025/09/08 16:33:53 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	cleanup_tokens(t_data *data)
{
	t_token	*traverser;
	t_token	*temp;

	if (data->tokens == NULL)
		return ;
	traverser = data->tokens;
	while (traverser != NULL)
	{
		temp = traverser;
		traverser = traverser->next;
		if (temp->value)
			free(temp->value);
		free(temp);
	}
	data->tokens = NULL;
}

void	cleanup_heredoc(int prcs_index)
{
	char	*here_doc_path;
	char	*prcs_index_number;

	prcs_index_number = ft_itoa(prcs_index);
	here_doc_path = ft_strjoin("/tmp/.here_doc", prcs_index_number);
	if (access(here_doc_path, F_OK) == 0)
		unlink(here_doc_path);
	(free(here_doc_path), free(prcs_index_number));
}

void	cleanup_argv(t_prcs *process)
{
	int	i;

	i = 0;
	while (process->argv[i] != NULL)
	{
		free(process->argv[i]);
		i++;
	}
	free(process->argv);
}

void	cleanup_processes(t_data *data)
{
	int	i;

	i = 0;
	while (data->processes[i] != NULL)
	{
		cleanup_heredoc(i);
		cleanup_argv(data->processes[i]);
		free(data->processes[i]);
		i++;
	}
	free(data->processes);
}
