/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:32:21 by skirwan           #+#    #+#             */
/*   Updated: 2025/08/11 13:33:43 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	invalid_export_identifier(t_data *data, char *to_export)
{
	write (STDERR_FILENO, "export: `", 9);
	write (STDERR_FILENO, to_export, ft_strlen(to_export));
	write (STDERR_FILENO, "': not a valid identifier\n", 26);
	data->exit_status = EXIT_FAILURE;
	return ;
}
