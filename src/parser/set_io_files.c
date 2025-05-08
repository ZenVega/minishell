/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_io_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:21:47 by jhelbig           #+#    #+#             */
/*   Updated: 2025/05/07 11:11:20 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../malloc_list/malloc_list.h"

char **redirection_split(char **args)
{
    char	**new;
	int		i;
	int		j;
	int		k;
	
	new = (char **)malloc(sizeof(char *) * 256);
    i = 0;
	j = 0;
    while (args[i])
    {
		if (args[i][0] == '\'' || args[i][0] == '\"')
		{
			new[j++] = ft_strdup(args[i]);
			i++;
			continue ;
        }
		k = 0;
        while (args[i][k])
        {
            if (args[i][k] == '>' || args[i][k] == '<')
            {
                if (k > 0)
				{
                    new[j++] = ft_substr(args[i], 0, k); //part before
                	if (!new[j - 1])
						return (free_var_arr(new), NULL);
				}
				if ((args[i][k] == '>' && args[i][k + 1] == '>' )
					|| (args[i][k] == '<' && args[i][k + 1] == '<'))
                {
                    new[j++] = ft_substr(args[i] + k, 0, 2); //2 versions of redirection arrows
                    if (!new[j - 1])
						return (free_var_arr(new), NULL);
					k += 2;
                }
                else
                {
                    new[j++] = ft_substr(args[i] + k, 0, 1);
                    if (!new[j - 1])
                         return (free_var_arr(new), NULL);
					k++;
                }
                args[i] = args[i] + k;
                k = 0;
            }
            else
                k++;
        }
        if (*args[i])
		{
            new[j++] = ft_strdup(args[i]); // part after
        	if (!new[j - 1])
 				return (free_var_arr(new), NULL);
		}
		i++;
    }
    new[j] = NULL;
    return (new);
}

//getting the split input
//looking for > and < to set infile and output
int	set_io_files(char *line, t_cmd_info *cmd, t_list **malloc_list, int *mask)
{
	char	**split;
	int		err;

	split = ft_split_safe(line, ' ', mask);
	if (!split)
		return (set_err(cmd, ERR_MALLOC, NULL), -1);
	add_list_to_malloc_list(malloc_list, (void *)split);
	split = redirection_split(split);
	if (!split)
		return (set_err(cmd, ERR_MALLOC, NULL), -1);
	add_list_to_malloc_list(malloc_list, (void *)split);
	err = set_infile(split, cmd);
	if (err != 0)
		return (set_err(cmd, ERR_NO_FILE, NULL));
	err = set_outfile(split, cmd);
	if (err != 0)
		return (set_err(cmd, ERR_NO_FILE, NULL));
	trim_args(split, cmd);
	return (0);
}

//if args are in quotation marks, they will not be kicked out here, because we look for
//redirection symbols in the 0 position
void	trim_args(char **args, t_cmd_info *cmd)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (args[i])
	{
		if (args[i][0] == '>' || args[i][0] == '<')
			i = i + 2;
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
