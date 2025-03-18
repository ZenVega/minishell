/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:15:18 by jhelbig           #+#    #+#             */
/*   Updated: 2025/03/18 11:43:29 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_args_split(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

// given infile_name does not exist or not possible to open
void	no_infile(char **args, char *file_name)
{
	ft_printf("No such file or directory: %s\n", file_name);
	free_args_split(args);
	exit(1);
}

void	parse_error_near_nl(char **args)
{
	ft_printf("parse error near '\\n'\n");
	free_args_split(args);
	exit(1);
}
