/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:21:47 by jhelbig           #+#    #+#             */
/*   Updated: 2025/03/18 10:10:18 by jhelbig          ###   ########.fr       */
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
	char	*file;

	i = 0;
	while (args[i])
	{
		//option 1)
		if ((args[i][0] == '<') && (ft_strlen(args[i]) > 1))
		{
		ft_printf("args [i]: %s\n", args[i]);
			file = ft_strtrim(args[i], (const char *) "<");
		ft_printf("file: %s\n", file);
			cmd->infile = open(file, O_RDONLY);
			// TO DO: ERROR-HANDLING
			free(file);
			args[i] = NULL;
		}
		//option 2)
		else if (args[i][0] == '<' && ft_strlen(args[i]) == 1)
		{
			// TO DO: error if < is last char* --> no infile given
			file = args[i + 1];
			cmd->infile = open(file, O_RDONLY);
			// TO DO: error handling if not possible to open
			args[i] = NULL;
			args[i + 1] = NULL;
		}
		i++;
	}	
}
