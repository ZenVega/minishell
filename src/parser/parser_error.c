/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:15:18 by jhelbig           #+#    #+#             */
/*   Updated: 2025/03/19 09:32:16 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

/*
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
*/

// given infile_name does not exist or not possible to open
void	no_infile(char *file_name, t_list **malloc_list)
{
	ft_printf("No such file or directory: %s\n", file_name);
	ft_lstclear(malloc_list, free);
	exit(1);
}

void	parse_error_near_nl(t_list **malloc_list)
{
	ft_printf("parse error near '\\n'\n");
	ft_lstclear(malloc_list, free);
	exit(1);
}
