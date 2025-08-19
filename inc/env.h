/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:55:35 by cbitca            #+#    #+#             */
/*   Updated: 2025/08/11 13:46:48 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

<<<<<<< HEAD:src/env/env.h
typedef struct s_token		t_token;
typedef struct s_lexer		t_lexer;
typedef struct s_data		t_data;

typedef struct s_env_var
{
	char				*key;
	char				*value;
	struct s_env_var	*next;
}	t_env_var;

t_env_var	*parse_env(t_env_var *env, char **env_var);
void		append_stack(t_env_var **node_lst, t_env_var *new);
char		*find_env(t_env_var *node, char *find);
t_env_var	*new_node(char *key, char *value);
t_env_var	*stack_last(t_env_var *first);
=======
# include "minishell.h"

//parse_env.c
t_env_var	*stack_last(t_env_var *first);
t_env_var	*new_node(char *key, char *value);
void		append_stack(t_env_var **node_lst, t_env_var *new);
void		parse_env(t_data *data, char **env_var);

//find_env.c
char		*find_env(t_env_var *env_list, char *key_to_find);
t_env_var	*find_env_node(t_env_var *env_list, char *key_to_find);
>>>>>>> skirwan:inc/env.h

#endif
