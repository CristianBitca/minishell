/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:35:27 by skirwan           #+#    #+#             */
/*   Updated: 2025/09/17 13:17:44 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "input.h"
#include "lexer.h"
#include "expansion.h"
#include "parser.h"
#include "built_in.h"
#include "ms_signals.h"

void	test_env(t_data *data)
{
	t_env_var	*node;

	node = data->env;
	while (node != NULL)
	{
		printf("key = %s\n", node->key);
		printf("value = %s\n", node->value);
		printf("\n");
		node = node->next;
	}
}

// Runs in an infinite loop, prompt is created new on each iteration
// so it can update the exit status and cwd. Readline will display
// prompt and return string taken from stdin. If we are given input
// we enter the next stage, tokenising the input and checking for
// invalid syntax. Then we expand variables through the token chain,
// splitting the words and inserting new tokens if necessary. After
// we take our token chain and convert it into an array of our prcs
// structure, which only requires an infile, outfile and argv. Then
// we execute our processes, cleanup memory in token chain and processes
// array, and return to the prompt to start again.
void	rl_loop(t_data *data)
{
	char	*input;
	char	*prompt;

	while (1)
	{
		sig_actions_interactive();
		prompt = create_prompt(data->exit_status);
		input = readline(prompt);
		free(prompt);
		if (input == NULL)
			full_exit(data, -1);
		if (input && *input)
		{
			add_history(input);
			if (tokenise(data, input) == -1)
			{
				cleanup_tokens(data);
				continue ;
			}
			if (validate_tokens(data) == -1)
			{
				cleanup_tokens(data);
				continue ;
			}
			expand(data);
			create_processes(data);
			if (count_processes(data) > 1)
				execute_all_processes(data, count_processes(data));
			else
				single_cmd(data, data->processes[0]);
			cleanup_tokens(data);
			cleanup_processes(data);
		}
	}
	return ;
}

// Creates a prompt as a malloced string (must be malloced to concatenate
// the string), displaying exit status and cwd.
char	*create_prompt(int exit_status)
{
	char	*ex_status;
	char	*prompt;
	char	*cwd;
	int		p_size;
	int		i;

	cwd = getcwd(NULL, 0);
	ex_status = ft_itoa(exit_status);
	p_size = ft_strlen(cwd) + ft_strlen(ex_status) + 5;
	prompt = malloc (p_size * sizeof(*prompt));
	prompt[0] = '[';
	i = (ft_strlcpy(&prompt[1], ex_status, (p_size - 1))) + 1;
	prompt[i] = ']';
	i += ft_strlcpy(&prompt[i + 1], cwd, (p_size - (i + 1)));
	prompt[i + 1] = '$';
	prompt[i + 2] = ' ';
	prompt[i + 3] = '\0';
	(free(cwd), free(ex_status));
	return (prompt);
}
