/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:55:35 by cbitca            #+#    #+#             */
/*   Updated: 2025/06/18 17:38:43 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

t_env_var	*stack_last(t_env_var *first);
t_env_var	*new_node(char *key, char *value);
void		append_stack(t_env_var **node_lst, t_env_var *new);
void		parse_env(t_data *data, char **env_var);
char		*find_env(t_env_var *node, char *find);
t_env_var	*find_env_node(t_env_var *node, char *key_to_find);

#endif
