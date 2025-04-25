/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_io_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:21:47 by jhelbig           #+#    #+#             */
/*   Updated: 2025/04/25 13:58:27 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../malloc_list/malloc_list.h"

//getting the split input
//looking for > and < to set infile and output
int	set_io_files(char *line, t_cmd_info *cmd, t_list **malloc_list, int *mask)
{
	char	**split;
	int		err;

	split = ft_split_safe(line, ' ', mask);
	if (!split)
		return (-1);
	add_list_to_malloc_list(malloc_list, (void *)split);
	err = set_infile(split, cmd);
	if (err != 0)
		return (err);
	err = set_outfile(split, cmd);
	if (err != 0)
		return (err);
	trim_args(split, cmd);
	return (0);
}

void	trim_args(char **args, t_cmd_info *cmd)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (args[i])
	{
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
