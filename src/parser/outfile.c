/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:20:23 by jhelbig           #+#    #+#             */
/*   Updated: 2025/05/19 17:10:04 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	truncate_outfile(char *file_name, t_cmd_info *cmd)
{
	clean_arg(file_name);
	if (cmd->outfile != STDOUT_FILENO)
		close(cmd->outfile);
	cmd->outfile = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (cmd->outfile < 0)
		return (set_err(cmd, ERR_PERM, file_name));
	return (0);
}

static int	append_outfile(char *file_name, t_cmd_info *cmd)
{
	clean_arg(file_name);
	if (cmd->outfile != STDOUT_FILENO)
		close(cmd->outfile);
	cmd->outfile = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (cmd->outfile < 0)
		return (set_err(cmd, ERR_PERM, file_name));
	return (0);
}

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
	if (args[i + 1])
	{
		if (args[i + 1][0] && (args[i + 1][0] == '>' || args[i + 1][0] == '<'))
			return (set_err(cmd, ERR_SYNTAX, "after >"));
	}
	else
		return (set_err(cmd, ERR_SYNTAX, "after >"));
	if (ft_strlen(args[i]) == 1)
		return (truncate_outfile(args[i + 1], cmd));
	else if (args[i][1] == '>')
		return (append_outfile(args[i + 1], cmd));
	return (0);
}
