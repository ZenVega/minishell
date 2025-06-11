/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_io_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:21:47 by jhelbig           #+#    #+#             */
/*   Updated: 2025/05/20 14:31:24 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../malloc_list/malloc_list.h"

static int	apnd(char **new, const char *src, int len, int *j)
{
	new[(*j)++] = ft_substr(src, 0, len);
	if (!new[(*j) - 1])
		return (-1);
	return (0);
}

static int	split_redirections(char **new, char *arg, int *j)
{
	int	i[2];

	i[0] = -1;
	i[1] = 0;
	while (arg[i[1] + ++i[0]])
	{
		if (arg[i[1] + i[0]] == '>' || arg[i[1] + i[0]] == '<')
		{
			if (i[0] > 0 && apnd(new, arg + i[1], i[0], j) == -1)
				return (-1);
			if ((arg[i[1] + i[0]] == '>' && arg[i[1] + i[0] + 1] == '>')
				|| (arg[i[1] + i[0]] == '<' && arg[i[1] + i[0] + 1] == '<'))
			{
				if (apnd(new, arg + i[1] + i[0]++, 2, j) == -1 || i[0]++ == -7)
					return (-1);
			}
			else if (apnd(new, arg + i[1] + i[0]++, 1, j) == -1)
				return (-1);
			i[1] += i[0];
			i[0] = -1;
		}
	}
	if (i[0] > 0 && apnd(new, arg + i[1], i[0], j) == -1)
		return (-1);
	return (0);
}

static char	**redirection_split(char **args)
{
	char	**new;
	int		i;
	int		j;

	new = (char **)malloc(sizeof(char *) * 256);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (args[i])
	{
		if (args[i][0] == '\'' || args[i][0] == '\"')
		{
			new[j++] = ft_strdup(args[i]);
			if (!new[j - 1])
				return (free_var_arr(new), NULL);
			i++;
			continue ;
		}
		if (split_redirections(new, args[i], &j))
			return (free_var_arr(new), NULL);
		i++;
	}
	new[j] = NULL;
	return (new);
}

//if args are in quotation marks, they will not be kicked out here, 
//because we look for redirection symbols in the 0 position
static void	trim_args(char **args, t_cmd_info *cmd)
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

//getting the split input
//looking for > and < to set infile and output
int	set_io_files(char *line, t_cmd_info *cmd, t_app *app, int *mask)
{
	char	**split;
	int		err;

	split = ft_split_white_safe(line, mask);
	if (!split)
		return (set_err(cmd, ERR_MALLOC, NULL), -1);
	add_list_to_malloc_list(&app->malloc_list, (void *)split);
	split = redirection_split(split);
	if (!split)
		return (set_err(cmd, ERR_MALLOC, NULL), -1);
	add_list_to_malloc_list(&app->malloc_list, (void *)split);
	err = set_infile(app, split, cmd);
	if (err != 0)
		return (set_err(cmd, ERR_NO_FILE, NULL), 1);
	err = set_outfile(split, cmd);
	if (err)
		return (1);
	trim_args(split, cmd);
	return (0);
}
