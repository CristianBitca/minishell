/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_infiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:47:13 by skirwan           #+#    #+#             */
/*   Updated: 2025/08/19 14:58:37 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	open_infiles(t_token *first, int token_count)
{
	t_token	*traverser;
	int		infilefd;

	traverser = first;
	while (token_count--)
	{
		if (traverser->type == REDIR_IN)
			infilefd = 0;
	}
	return (infilefd);
}
