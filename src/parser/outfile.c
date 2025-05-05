/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:20:23 by jhelbig           #+#    #+#             */
/*   Updated: 2025/05/05 15:04:51 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	set_outfile(char **args, t_cmd_info *cmd)
{
	int		i;
	int		err;
	char	*addr;
	
	i = 0;
	while (args[i])
	{
		addr = ft_strchr(args[i], '>');
		if (addr)
		{
			err = found_outfile(args, i, addr, cmd);
			if (err != 0)
				return (err);
		}
		i++;
	}
	return (0);
}

int	found_outfile(char **args, int i, char *addr, t_cmd_info *cmd)
{
	char	*file_name;

	file_name = NULL;
	if (ft_strlen(addr) == 1)
	{
		if (args[i + 1])
			file_name = args[i + 1];
		else
			return (set_err(cmd, ERR_SYNTAX, "after >"));
		return (truncate_outfile(file_name, cmd));
	}
	else if (ft_strlen(addr) > 1)
	{
		// case >outfile
		if (*(addr + 1) != '>')
			return (truncate_outfile(addr + 1, cmd));
        //case_append outfile >>
		else if (*(addr + 1) == '>')
			return (append_outfile(args, i, addr, cmd));
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
		return (set_err(cmd, ERR_NO_FILE, file_name));
	return (0);
}

int	append_outfile(char **args, int i, char *addr, t_cmd_info *cmd)
{
	char	*file_name;

	if (cmd->outfile != STDOUT_FILENO)
		close(cmd->outfile);
    // case >> outfile
	if (ft_strlen(addr) == 2)
	{
		if (args[i + 1])
			file_name = args[i + 1];
		else
			return (set_err(cmd, ERR_SYNTAX, "after >"));
		cmd->outfile = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (cmd->outfile < 0)
			return (set_err(cmd, ERR_NO_FILE, file_name));
	}
    // case >>outfile
	else if (ft_strlen(addr) > 2)
	{
		cmd->outfile = open(addr + 2, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (cmd->outfile < 0)
			return (304);
	}
	return (0);
}
