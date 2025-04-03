/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:00:35 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/27 14:06:50 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

t_parser_info	init_parser_info(int infile, int outfile, char *line)
{
	t_parser_info	p_info;

	p_info.infile = infile;
	p_info.outfile = outfile;
	p_info.line = line;
	return (p_info);
}

//  all possible checks
//  cmd_info has all necessary keys set
//  argv[0] has no special characters
//  ...
int	is_valid(t_cmd_info *cmd)
{
	t_cmd_info	cmd_err;

	cmd_err.err_info.code = ERR_MALLOC;
	if (cmd == NULL)
		return (exit_with_error(cmd_err));
	//TODO: not sure if there are more unvalid cases
	return (0);
}

void	reroute_io(int input, int output)
{
	if (input != STDIN_FILENO)
		dup2(input, STDIN_FILENO);
	if (output != STDOUT_FILENO)
		dup2(output, STDOUT_FILENO);
}

// TODO: This function is deprecated.
// Since parts of it might be a good example of how to use *dir functions, Ill keep it here
// as an example. MUST BE DELETED before launch
int	is_in_path(char *path, char *cmd_name)
{
	DIR				*dir_ptr;
	struct dirent	*dir_entity;
	int				found;

	dir_ptr = opendir(path);
	found = 0;
	if (!dir_ptr)
		return (-1);
	while (1)
	{
		dir_entity = readdir(dir_ptr);
		if (!dir_entity)
			break ;
		if (!ft_strcmp(dir_entity->d_name, cmd_name))
		{
			found = 1;
			break ;
		}
	}
	closedir(dir_ptr);
	if (found)
		return (0);
	return (1);
}
