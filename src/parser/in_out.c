/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:21:47 by jhelbig           #+#    #+#             */
/*   Updated: 2025/03/18 11:49:44 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "parser.h"

//getting the split input
//looking for > and < to set infile and output
void	in_out(char **args, t_cmd_info *cmd)
{
	set_infile(args, cmd);
	//set_outfile(args, cmd);
	//trim_args(args);
}

// finding > in splits and set infile
//options: 1) >infile 2) > infile
void	set_infile(char **args, t_cmd_info *cmd)
{
	int		i;
	char	*file_name;

	i = 0;
	while (args[i])
	{
		if ((args[i][0] == '<') && (ft_strlen(args[i]) > 1) && args[i][1] != '<')
		{
			file_name = ft_strtrim(args[i], (const char *) "<");
			cmd->infile = open(file_name, O_RDONLY);
			if (cmd->infile < 0)
				no_infile(args, file_name);
			free(file_name);
		}
		else if (args[i][0] == '<' && ft_strlen(args[i]) == 1)
		{
			if (args[i + 1])
				file_name = args[i + 1];
			else
				parse_error_near_nl(args);
			cmd->infile = open(file_name, O_RDONLY);
			if (cmd->infile < 0)
				no_infile(args, file_name);
		}
		i++;
	}	
}
