/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:47:04 by skirwan           #+#    #+#             */
/*   Updated: 2025/09/25 16:13:16 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ms_signals.h"

extern volatile int g_signal;

// Sig_handlers should be very basic, so we use the global variable g_signal
// as a way to communicate signals have been received throughout the program,
// and execute more complext code when received. When waiting for prompt input
// this is our handler for SIGINT, we just set the g_signal to SIGINT which
// allows us to handle the signal in our input loop. Also we set rl_done to 1
// which is a global variable in the readline library, when it is non-zero
// value it communicates to the other functions in the library to stop reading
// input and return the current line buffer.
void	sig_handlers_interactive(int signal)
{
	if (signal == SIGINT)
		g_signal = SIGINT;
	rl_done = 1;
}

// sigaction struct is defined in <signals.h>, it holds variables used
// for the sigaction function. All we need is the sa_handler, so we ft_bzero
// the whole struct so there are no issues with uninitialised variables or
// conflicts between sa_handler and sa_sigaction (sa_handler and sa_sigaction
// cannot both be initialised at the same time). Then we set the handler
// to a pointer of the function we wish to call when we intercept the signal,
// and finally use the sigaction function to replace the given signal's
// default handling with our own function.
void	sigactions_interactive(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &sig_handlers_interactive;
	sigaction(SIGINT, &act, NULL);
	ft_bzero(&act, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

// Before forking, in the parent process we want to ignore all signals
// so that signals intented for the child are not intercepted, or so that
// signal handlers are not duplicated.
void	parent_sigactions_pre_fork(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

// Resets signal handlers to default handlers, called in the child process
// so that signals sent to children after execve are handled however they
// are predefined in the command called by execve.
void	sig_actions_default(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = SIG_DFL;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
