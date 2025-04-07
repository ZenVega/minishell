/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:20:09 by jhelbig           #+#    #+#             */
/*   Updated: 2025/04/02 11:09:05 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "parser.h"
#include "../malloc_list/malloc_list.h"

// finding > in splits and set infile
//options: 1) >infile 2) > infile

// circling through all the argument parts, multiple infiles are just overwritten by following
int	set_infile(char **args, t_cmd_info *cmd)
{
	int		i;
	int		err;

	i = 0;
	while (args[i])
	{	
		if (args[i][0] == '<')
		{
			err = found_infile(args, i, cmd);	
			if (err != 0)
				return (err);
		}
		i++;
	}
	return (0);	
}

int    found_infile(char **args, int i, t_cmd_info *cmd)
{
    char	*file_name;

    file_name = NULL;
    // case < infile
	if (ft_strlen(args[i]) == 1)
	{
		if (args[i + 1])
			file_name = args[i + 1];
		else
			return (301);
		return (simple_infile(file_name, cmd));
	}
	if (ft_strlen(args[i]) > 1)
	{
        // case <infile
		if (args[i][1] != '<')
			return (simple_infile(args[i] + 1, cmd));
		//here_doc <<
		    //if (args[i][1] == '<')
			//here_doc(args, i, cmd, malloc_list);	
	}
	return (0);
}

int    simple_infile(char *file_name, t_cmd_info *cmd)
{
	if (cmd->infile != STDIN_FILENO)
		close(cmd->infile);
    cmd->infile = open(file_name, O_RDONLY);
	if (cmd->infile < 0)
		return (302);
	return (0);
}
