/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:29:53 by jhelbig           #+#    #+#             */
/*   Updated: 2025/03/12 14:17:38 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char *clean_filename(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if ((filename[0] == '\"' && filename[len - 1] == '\"')
		|| (filename[0] == '\'' && filename[len - 1] == '\''))
	{
		ft_memmove(filename, filename + 1, len - 2);
		filename[len - 2] = '\0';
	}
	return (filename);
}
