/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:20:42 by cbitca            #+#    #+#             */
/*   Updated: 2025/06/18 16:20:43 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*ft_joinchar(char *s, char c)
{
	char	*buffer;
	int		l;

	l = ft_strlen(s);
	buffer = ft_calloc(l + 2, sizeof(char));
	if (!buffer)
		return (0);
	ft_strcpy(buffer, s);
	buffer[l + 1] = c;
	buffer[l + 2] = '\0';
	free(s);
	return (buffer);
}