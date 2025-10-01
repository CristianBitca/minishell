/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:35:27 by skirwan           #+#    #+#             */
/*   Updated: 2025/09/26 15:08:03 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "input.h"
#include "lexer.h"
#include "expansion.h"
#include "env.h"
#include "parser.h"
#include "built_in.h"
#include "ms_signals.h"
#include <stdlib.h>

extern volatile int g_signal;

void	print_tokens(t_data *data)
{

	//test func to be deleted
	t_token	*token;
	char	*number;

	token = data->tokens;
	while (token != NULL)
	{
		if (*token->value == '\0')
			printf("token value = NULL\n");
		else
			printf("token value = %s\n", token->value);
		number = ft_itoa(token->type);
		printf("token type = %s\n", number);
		printf("*******\n");
		token = token->next;
		if (number)
			free(number);
	}
}

// Readline will display the prompt created and return string taken from
// stdin stream. First we set the rl_event_hook function pointer to our own
// function ms_rl_event, which just returns 0. This event hook runs ten
// times every second while there are no keystrokes and is set by default to
// NULL (no function). Therefore we point the event hook to our function that
// does nothing so that the loop in the readline function is interrupted,
// therefore we can execute code that follows after the call to readline,
// which is our signal handler.
// We run this in an infinite loop to handle signals. If we
// receive SIGINT, we empty the current line buffer with rl_replace_line,
// giving an empty string. Then we reset the g_signal, set our exit_status
// to the correct exit code for SIGINT (130), and restart the loop to display
// the prompt again and wait for input. We have to reallocate the prompt each
// time because the exit_status can change from what it was previously to 130.
char	*get_input(t_data *data)
{
	char	*input;
	char	*prompt;

	rl_event_hook = &ms_rl_event;
	while (1)
	{
		prompt = create_prompt(data->exit_status);
		if (isatty(fileno(stdin)))
			input = readline(prompt);
		else
		{
			char *line;
			line = ft_get_next_line(fileno(stdin));
			input = ft_strtrim(line, "\n");
			free(line);
		}
		free(prompt);
		if (g_signal == SIGINT)
		{
			rl_replace_line("", 1);
			g_signal = 0;
			data->exit_status = 130;
			continue ;
		}
		if (input == NULL)
			full_exit(data, -1);
		else
			break ;
	}
	return (input);
}

// After input from readline (get_input function),
// If we are given input we enter the next stage, tokenising the input
// and checking for invalid syntax. Then we expand variables through
// the token chain, splitting the words and inserting new tokens if necessary.
// After we take our token chain and convert it into an array of our prcs
// structure, which only requires an infile, outfile and argv. Then
// we execute our processes, cleanup memory in token chain and processes
// array, and return to the prompt to start again.
void	rl_loop(t_data *data)
{
	char	*input;

	while (1)
	{
		sigactions_interactive();
		input = get_input(data);
		if (input && *input)
		{
			add_history(input);
			if (tokenise(data, input) == -1)
			{
				cleanup_tokens(data);
				continue ;
			}
			// printf("Before\n");
			// print_tokens(data);
			expand(data);
			// printf("After\n");
			// print_tokens(data);
			if (create_processes(data) == -2)
			{
				(cleanup_tokens(data), cleanup_processes(data));
				continue ;
			}
			if (count_processes(data) > 1)
				execute_all_processes(data, count_processes(data));
			else
				single_cmd(data, data->processes[0]);
			(cleanup_tokens(data), cleanup_processes(data));
		}
	}
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
