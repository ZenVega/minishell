/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:20:09 by jhelbig           #+#    #+#             */
/*   Updated: 2025/03/21 14:08:18 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "parser.h"
#include "../malloc_list/malloc_list.h"

// finding > in splits and set infile
//options: 1) >infile 2) > infile

void	set_infile(char **args, t_cmd_info *cmd, t_list **malloc_list)
{
	int		i;

	i = 0;
	while (args[i])
	{	
		if (args[i][0] == '<')
			found_infile(args, i, cmd, malloc_list);	
	i++;
	}	
}

void    found_infile(char **args, int i, t_cmd_info *cmd, t_list **malloc_list)
{
    char	*file_name;

    file_name = NULL;
    // case < infile
	if (ft_strlen(args[i]) == 1)
	{
		if (args[i + 1])
			file_name = args[i + 1];
		else
			parse_error_near_nl(malloc_list);
		simple_infile(file_name, cmd, malloc_list);
	}
	if (ft_strlen(args[i]) > 1)
	{
        // case <infile
		if (args[i][1] != '<')
			simple_infile(args[i] + 1, cmd, malloc_list);
		//here_doc <<
		    //if (args[i][1] == '<')
			//here_doc(args, i, cmd, malloc_list);	
	}
}

void    simple_infile(char *file_name, t_cmd_info *cmd, t_list **malloc_list)
{
    cmd->infile = open(file_name, O_RDONLY);
	if (cmd->infile < 0)
		no_infile(file_name, malloc_list);
}
