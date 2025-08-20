/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:35:27 by skirwan           #+#    #+#             */
/*   Updated: 2025/08/07 10:46:07 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "input.h"
#include "lexer.h"
#include "expansion.h"

void	print_tokens(t_data *data)
{

	//test func to be deleted
	t_token	*token;

	token = data->tokens;
	while (token != NULL)
	{
		if (*token->value == '\0')
			printf("token value = NULL\n");
		else
			printf("token value = %s\n", token->value);
		printf("token type = %s\n", ft_itoa(token->type));
		printf("*******\n");
		token = token->next;
	}
}



void	rl_loop(t_data *data)
{
	char	*input;
	char	*prompt;

	prompt = create_prompt(data);
	input = readline(prompt);
	free(prompt);
	if (input && *input)
	{
		add_history(input);
		tokenise(data, input);
		// validate_tokens(data);
		printf("**********************************\n");
		printf("token chain pre expansion:\n:");
		print_tokens(data);
		expand(data);
		printf("**********************************\n");
		printf("token chain post expansion:\n");
		print_tokens(data);
		//parse(input)
		//(execute)
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
