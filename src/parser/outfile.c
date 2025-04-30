/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:20:23 by jhelbig           #+#    #+#             */
/*   Updated: 2025/04/02 11:11:32 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	set_outfile(char **args, t_cmd_info *cmd)
{
	int		i;
	int		err;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '>')
		{
			err = found_outfile(args, i, cmd);
			if (err != 0)
				return (err);
		}
		i++;
	}
	return (0);
}

int	found_outfile(char **args, int i, t_cmd_info *cmd)
{
	char	*file_name;

	file_name = NULL;
	if (ft_strlen(args[i]) == 1)
	{
		if (args[i + 1])
			file_name = args[i + 1];
		else
			return (set_err(cmd, ERR_SYNTAX, "outfile"));
		return (truncate_outfile(file_name, cmd));
	}
	else if (ft_strlen(args[i]) > 1)
	{
		// case >outfile
		if (args[i][1] != '>')
			return (truncate_outfile(args[i] + 1, cmd));
        //case_append outfile >>
		else if (args[i][1] == '>')
			return (append_outfile(args, i, cmd));
	}
	return (0);
}

int	truncate_outfile(char *file_name, t_cmd_info *cmd)
{
	if (cmd->outfile != STDOUT_FILENO)
		close(cmd->outfile);
	cmd->outfile = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (cmd->outfile < 0)
        //could not open outfile error here
		return (set_err(cmd, ERR_NO_FILE, "outfile"));
	return (0);
}

int	append_outfile(char **args, int i, t_cmd_info *cmd)
{
	char	*file_name;

	if (cmd->outfile != STDOUT_FILENO)
		close(cmd->outfile);
    // case >> outfile
	if (ft_strlen(args[i]) == 2)
	{
		if (args[i + 1])
			file_name = args[i + 1];
		else
			return (set_err(cmd, ERR_SYNTAX, "outfile"));
		cmd->outfile = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (cmd->outfile < 0)
			return (set_err(cmd, ERR_NO_FILE, "outfile"));
	}
    // case >>outfile
	else if (ft_strlen(args[i]) > 2)
	{
		cmd->outfile = open(args[i] + 2, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (cmd->outfile < 0)
			return (304);
	}
	return (0);
}
