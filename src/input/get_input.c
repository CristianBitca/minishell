/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:35:27 by skirwan           #+#    #+#             */
/*   Updated: 2025/06/18 11:55:16 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "input.h"

char	*rl_loop(t_data *data)
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
			input_to_cmd(data, input);
			add_history(input);
		}
	}
	return (input);
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

void	input_to_cmd(t_data *data, char *input)
{
	char	**s_argv;
	t_cmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	s_argv = ft_split(input, ' ');
	cmd->argv = s_argv;
	cmd->infilefd = 0;
	cmd->outfilefd = 1;
	ft_lstadd_back(&data->cmd_list, ft_lstnew(cmd));
}
