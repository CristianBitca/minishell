/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:49:15 by skirwan           #+#    #+#             */
/*   Updated: 2025/09/10 12:02:51 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "built_in.h"

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
		if (temp->type == WORD)
			free(temp->value);
		free(temp);
	}
	data->tokens = NULL;
}

void	cleanup_heredoc(t_data *data, int prcs_index)
{
	char	*here_doc_path;
	char	*prcs_index_number;

	prcs_index_number = ft_itoa(prcs_index);
	here_doc_path = ft_strjoin("/tmp/.here_doc", prcs_index_number);
	if (access(here_doc_path, F_OK) == 0)
	{
		if (unlink(here_doc_path) == -1)
		{
			perror(NULL);
			data->exit_status = 1;
		}
	}
	(free(here_doc_path), free(prcs_index_number));
}

void	cleanup_argv(t_prcs *process)
{
	int	i;

	if (process->argv == NULL)
		return ;
	i = 0;
	while (process->argv[i] != NULL)
	{
		free(process->argv[i]);
		i++;
	}
	free(process->argv);
	process->argv = NULL;
}

void	cleanup_processes(t_data *data)
{
	int	i;

	if (data->processes == NULL)
		return ;
	i = 0;
	while (data->processes[i] != NULL)
	{
		cleanup_heredoc(data, i);
		cleanup_argv(data->processes[i]);
		free(data->processes[i]);
		i++;
	}
	free(data->processes);
	data->processes = NULL;
}

void	cleanup_env(t_data *data)
{
	t_env_var	*traverser;
	t_env_var	*temp;

	if (data->env == NULL)
		return ;
	traverser = data->env;
	while (traverser != NULL)
	{
		temp = traverser;
		traverser = traverser->next;
		(free(temp->key), free(temp->value));
		free(temp);
	}
	data->env = NULL;
}
