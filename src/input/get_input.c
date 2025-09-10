/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:35:27 by skirwan           #+#    #+#             */
/*   Updated: 2025/09/08 16:29:41 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "input.h"
#include "lexer.h"
#include "expansion.h"
#include "parser.h"
#include "built_in.h"

void	rl_loop(t_data *data)
{
	char	*input;
	char	*prompt;

	while (1)
	{
		prompt = create_prompt(data);
		input = readline(prompt);
		free(prompt);
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
			if (create_processes(data) == -1)
				continue ;
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

char	*create_prompt(t_data *data)
{
	char	*ex_status;
	char	*prompt;
	char	*cwd;
	int		p_size;
	int		i;

	cwd = getcwd(NULL, 0);
	ex_status = ft_itoa(data->exit_status);
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
