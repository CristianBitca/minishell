/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:47:29 by skirwan           #+#    #+#             */
/*   Updated: 2025/09/17 12:56:57 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_SIGNALS_H
# define MS_SIGNALS_H

// signal_handlers.c
void	sig_handlers_interactive(int signal);
void	sigactions_interactive(void);
void	parent_sigactions_pre_fork(void);
void	sig_actions_default(void);

// ms_rl_hooks.c
int	ms_rl_event(void);

#endif