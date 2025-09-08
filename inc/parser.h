/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:27:29 by skirwan           #+#    #+#             */
/*   Updated: 2025/09/03 10:22:10 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

// here_doc.c
char	*create_here_doc_temp_file_path(int prcs_index);
int	convert_here_docs(t_data *data, int token_count, int prcs_index);
char	*here_doc_readline(t_data *data, int here_doc_fd, char *delimiter, int	*exp_flag);
int	read_here_doc(t_data *data, char *delimiter, char *here_doc_path);

// create_processes.c
int		count_processes(t_data *data);
int		allocate_processes(t_data *data);
void	create_processes(t_data *data);

// parse_process.c
void	assign_prcs(t_data *data, t_token *first, int tok_c, int prcs_index);

// open_infiles.c
int		check_infile_permissions(char *file_path);
int		*create_infilefds_array(t_token *traverser, int token_count);
int		open_infile(int *fds, int fd_index, char *file_path);
int		close_redundant_fds(int **fds, int fds_index);
int		handle_infiles(t_token *first, int token_count);

// open_outfiles.c
int	*create_outfilefds_array(t_token *traverser, int token_count);
int	check_outfile_permissions(char *file_path);
int	open_outfile(int *fds, int fd_index, char *file_path, int type);
int	handle_outfiles(t_token *traverser, int token_count);

// make_argv.c
int		count_arguments(t_token *traverser, int token_count);
char	**make_process_argv(t_data *data, t_token *traverser, int token_count);

// create_command.c
int		check_valid_file(char *cmd);
char	*create_command(t_data *data, char *cmd);

#endif
