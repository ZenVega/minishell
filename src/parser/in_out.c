/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:21:47 by jhelbig           #+#    #+#             */
/*   Updated: 2025/03/19 09:24:05 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "parser.h"
#include "../malloc_list/malloc_list.h"

//getting the split input
//looking for > and < to set infile and output
void	in_out(char **args, t_cmd_info *cmd, t_list **malloc_list)
{
	set_infile(args, cmd, malloc_list);
	//set_outfile(args, cmd);
	//trim_args(args);
}

// finding > in splits and set infile
//options: 1) >infile 2) > infile
void	set_infile(char **args, t_cmd_info *cmd, t_list **malloc_list)
{
	int		i;
	char	*file_name;

	i = 0;
	while (args[i])
	{
		if ((args[i][0] == '<') && (ft_strlen(args[i]) > 1) && args[i][1] != '<')
		{
			file_name = ft_strtrim(args[i], (const char *) "<");
			add_to_malloc_list(malloc_list, (void *) file_name);
			cmd->infile = open(file_name, O_RDONLY);
			if (cmd->infile < 0)
				no_infile(file_name, malloc_list);
		}
		else if (args[i][0] == '<' && ft_strlen(args[i]) == 1)
		{
			if (args[i + 1])
				file_name = args[i + 1];
			else
				parse_error_near_nl(malloc_list);
			cmd->infile = open(file_name, O_RDONLY);
			if (cmd->infile < 0)
				no_infile(file_name, malloc_list);
		}
		i++;
	}	
}
