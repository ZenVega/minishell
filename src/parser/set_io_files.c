/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_io_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:21:47 by jhelbig           #+#    #+#             */
/*   Updated: 2025/03/31 11:52:57 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "parser.h"
#include "../malloc_list/malloc_list.h"

//getting the split input
//looking for > and < to set infile and output
int	set_io_files(char *line, t_cmd_info *cmd, t_list **malloc_list)
{
	char **split;
	
	split = ft_split(line, ' ');
	if (!split)
		return (-1);
	add_to_malloc_list(malloc_list, (void *)split);
	//multiple infiles are just overwritten
	set_infile(split, cmd, malloc_list);
	//multiple oufile are overwritten by last, but still opened/created/closed on the way
	set_outfile(split, cmd, malloc_list);
	trim_args(split, cmd);
	return (0);
}

void    trim_args(char **args, t_cmd_info *cmd)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j =	0; 

	while (args[i])
	{
		//case < infile, > outfile, >> outfile
		// 'delete' 2 args 
		if (((args[i][0] == '>' || args[i][0] == '<') && ft_strlen(args[i]) == 1) 
			|| (args[i][0] == '>' && args[i][1] == '>' && ft_strlen(args[i]) == 2))
				i = i + 2;
		else if (((args[i][0] == '>' || args[i][0] == '<') && ft_strlen(args[i]) > 1) 
             || (args[i][0] == '>' && args[i][1] == '>' && ft_strlen(args[i]) > 2))
				i++;
		else
		{	
			tmp = args[i];
			args[j] = tmp;
			j++;
			i++;
		}
	}
	while (j < i)
	{
		args[j] = NULL;
		j++;
	}
	cmd->args = args;
}

