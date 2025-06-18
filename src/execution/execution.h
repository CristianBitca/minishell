/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:25:42 by skirwan           #+#    #+#             */
/*   Updated: 2025/06/12 15:15:08 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"

typedef struct s_exe_data
{
	t_list		**cmd_list;
	int			**pipe_array;
}	t_exe_data;

t_allocations	*create_start(int argc, char **argv, char **envp);
t_list			*create_list(t_allocations *allocations);
int				**create_pipes(t_allocations *allocations);
int				open_infile(char **argv);

char			**find_paths(char **envp);
char			*create_path(char **paths, t_list *ptr);
t_list			*find_exe(t_allocations *allocations, char **paths);
void			cmd_not_found(char *exe);

void			exit_conditionally(int exit_flag, t_allocations *allocations);
void			free_list(t_list **list);
void			free_pipes(int **pipe_array);
void			check_flag(int exit_flag, t_allocations *allocations);

void			child_p(int i, t_list *ptr, t_allocations *allocations,
					pid_t *cpid);
void			last_cmd_fh(t_allocations *allocations, pid_t *cpid);
void			loop_cmds(t_allocations *allocations);
void			fork_and_exe(t_allocations *allocations, pid_t *cpid);
void			close_pipes(t_allocations *allocations, int i);

int				*here_doc(char **argv, int *pipe1);
void			read_hd(char *limiter, int temp_file);

t_allocations	*create_start_hd(int argc, char **argv, char **envp);
t_inputs		*take_inputs_hd(int argc, char **argv, char **envp);
t_list			*create_list_hd(t_allocations *allocations);
int				**create_pipes_hd(t_allocations *allocations);

#endif
