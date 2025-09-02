/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:27:29 by skirwan           #+#    #+#             */
/*   Updated: 2025/08/28 12:47:21 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

// here_doc.c
char	*create_here_doc_temp_file_path(int prcs_indexdoc_count);
int		convert_here_docs(t_token *traverser, int token_count, int prcs_index);
int		read_here_doc(char *delimiter, char *here_doc_path);

// create_processes.c
int		allocate_processes(t_data *data);
void	create_processes(t_data *data);

// parse_process.c
void	assign_prcs(t_data *data, t_token *first, int token_count, int prcs_index);

// open_infiles.c
int		check_infile_permissions(char *file_path);
int		*create_infilefds_array(t_token *traverser, int token_count);
int		open_infile(int *fds, int fd_index, char *file_path);
int		close_infilefds(int **fds, int fds_index);
int		handle_infiles(t_token *first, int token_count);

#endif
