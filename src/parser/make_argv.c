/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:51:47 by skirwan           #+#    #+#             */
/*   Updated: 2026/03/19 09:45:11 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

int	count_arguments(t_token *traverser, int token_count)
{
	int	arg_count;

	arg_count = 0;
	while (token_count-- > 0 && traverser != NULL)
	{
		if (traverser->type == WORD)
		{
			if (traverser->prev == NULL || (traverser->prev->type == WORD
					|| traverser->prev->type == PIPE))
				arg_count++;
		}
		traverser = traverser->next;
	}
	return (arg_count);
}

char	*find_first_word(t_token *traverser, int token_count)
{
	while (token_count-- > 0 && traverser != NULL)
	{
		if (traverser->type == WORD)
		{
			if (traverser->prev == NULL || (traverser->prev->type == WORD
					|| traverser->prev->type == PIPE))
				return (traverser->value);
		}
		traverser = traverser->next;
	}
	return (NULL);
}

t_token	*move_past_first_word(t_token *traverser, int *token_count)
{
	int	count;

	count = *token_count;
	while (count-- > 0 && traverser != NULL)
	{
		if (traverser->type == WORD)
		{
			if (traverser->prev == NULL || (traverser->prev->type == WORD
					|| traverser->prev->type == PIPE))
			{
				*token_count = count;
				return (traverser->next);
			}
		}
		traverser = traverser->next;
	}
	*token_count = count;
	return (NULL);
}

void	add_arguments(char **argv, t_token *traverser, int token_count)
{
	int	i;

	i = 1;
	traverser = move_past_first_word(traverser, &token_count);
	while (token_count-- > 0 && traverser != NULL)
	{
		if (traverser->type == WORD && traverser->prev->type == WORD)
		{
			argv[i] = ft_strdup(traverser->value);
			i++;
		}
		traverser = traverser->next;
	}
}

char	**make_process_argv(t_data *data, t_token *traverser, int tokens)
{
	char	**argv;
	char	*first_word;
	char	*cmd;
	int		arg_count;

	arg_count = count_arguments(traverser, tokens);
	if (arg_count == 0)
		return (NULL);
	argv = ft_calloc(arg_count + 1, sizeof(*argv));
	first_word = find_first_word(traverser, tokens);
	if (is_built_in(first_word) == 1)
		cmd = ft_strdup(first_word);
	else if (check_valid_file(first_word) == -1)
		cmd = NULL;
	else if (check_exe_creation(data, first_word) == 0)
		cmd = ft_strdup(first_word);
	else
		cmd = create_command(data, first_word);
	argv[0] = cmd;
	add_arguments(argv, traverser, tokens);
	return (argv);
}
