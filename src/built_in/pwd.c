/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:01:47 by skirwan           #+#    #+#             */
/*   Updated: 2025/06/30 13:28:33 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "built_in.h"

void	pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	write(1, cwd, ft_strlen(cwd));
	write(1, "\n", 1);
	free(cwd);
}
