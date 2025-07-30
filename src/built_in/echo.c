/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 11:31:28 by skirwan           #+#    #+#             */
/*   Updated: 2025/07/06 17:34:42 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "built_in.h"

// valid options are -n, or '-' and any number of 'n' e.g
// -nnnnnnnn
int	check_n(char *str)
{
	if (str == NULL || *str == '\0')
		return (-1);
	if (*str == '-')
		str++;
	else
		return (1);
	while (*str)
	{
		if (*str == 'n')
			str++;
		else
			return (1);
	}
	if (*str != '\0')
		return (1);
	return (0);
}

// receives arguments char ** created by ft_split(' ').
// Checks -n option whether to print print_newline
// If first arg is valid -n, checks all successive args that are valid
// and doesnt write them to stdout.
// After -n checks, writes each arg to stdout and adds space between
// to bring back the space lost from ft_split
void	echo(char **args, int out_fd)
{
	int	print_newline;

	if (check_n(*args) == 1)
		print_newline = 1;
	else
	{
		print_newline = 0;
		while (check_n(*args) == 0)
			args++;
	}
	while (*args)
	{
		write (out_fd, *args, ft_strlen(*args));
		args++;
		if (*args)
			write (out_fd, " ", 1);
	}
	if (print_newline == 1)
		write (out_fd, "\n", 1);
}
