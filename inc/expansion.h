/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 12:16:37 by skirwan           #+#    #+#             */
/*   Updated: 2025/08/08 14:04:23 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "minishell.h"

// expand.c
void	check_to_expand(t_data *data, t_token *token);
void	expand(t_data *data);

// expand_env.c
void	expand_env(t_data *data, t_token *token, int i);

#endif
