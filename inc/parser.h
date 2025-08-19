/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:27:29 by skirwan           #+#    #+#             */
/*   Updated: 2025/08/19 14:16:58 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

// create_processes.c
int		allocate_processes(t_data *data);
void	create_processes(t_data *data);

// parse_process.c
void	assign_prcs(t_data *data, t_token *first, int token_count, int prcs_index);

// open_infiles.c
int		open_infiles(t_token *first, int token_count);

#endif
