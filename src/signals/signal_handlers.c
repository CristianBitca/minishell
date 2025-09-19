/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:47:04 by skirwan           #+#    #+#             */
/*   Updated: 2025/09/17 13:58:54 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "libft.h"
#include "ms_signals.h"

void	sig_handlers_interactive(int signal)
{
	char	*prompt;

	if (isatty(STDIN_FILENO) == 0)
		return ;
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		prompt = create_prompt(130);
		write(1, prompt, ft_strlen(prompt));
		free(prompt);
	}
	if (signal == SIGQUIT)
		return ;
}

// sigaction struct is defined in <signals.h>, it holds variables used
// for the sigaction function. All we need is the sa_handler, so we ft_bzero
// the whole struct so there are no issues with uninitialised variables or
// conflicts between sa_handler and sa_sigaction (sa_handler and sa_sigaction
// cannot both be initialised at the same time). Then we set the handler
// to a pointer of the function we wish to call when we intercept the signal,
// and finally use the sigaction function to replace the given signal's
// default handling with our own function.
void	sig_actions_interactive(void)
{
	struct sigaction	act;

	if (isatty(STDIN_FILENO) == 0)
		return ;
	ft_bzero(&act, sizeof(act));
	act.sa_handler = &sig_handlers_interactive;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

void	block_signals_pre_fork(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

void	sig_actions_default(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = SIG_DFL;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGINT, &act, NULL);
}
