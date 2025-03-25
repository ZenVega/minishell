/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:21:47 by jhelbig           #+#    #+#             */
/*   Updated: 2025/03/25 13:29:06 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "parser.h"
#include "../malloc_list/malloc_list.h"

//getting the split input
//looking for > and < to set infile and output
void	in_out(char *line, t_cmd_info *cmd, t_list **malloc_list)
{
	char **split;
	
	split = ft_split(line, ' ');
	add_to_malloc_list(malloc_list, (void *)split);
	set_infile(split, cmd, malloc_list);
	set_outfile(split, cmd, malloc_list);
	trim_args(split, cmd);
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

