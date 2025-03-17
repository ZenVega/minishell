/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:00:35 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/17 15:09:09 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

// isolates cmd_name from args** and writes it to dest
void	isolate_cmd_name(char *args, char **dest)
{
	size_t	i;

	i = 0;
	while (is_space(*args))
		args++;
	while (!is_space(args[i]))
		i++;
	//TODO: add track_malloc
	*dest = (char *)malloc(sizeof(char) * i);
	ft_strlcpy(*dest, args, i);
	ft_printf("CMD: %s\n", *dest);
}

//  all possible checks
//  cmd_info has all necessary keys set
//  argv[0] has no special characters
//  ...
int	is_valid(t_cmd_info *cmd)
{
	if (cmd->type != 0)
		return (1);
	return (0);
}

// iterates over each file in path and compares to cmd_name
int	is_in_path(char *path, char *cmd_name)
{
	DIR				*dir_ptr;
	struct dirent	*dir_entity;
	int				found;

	dir_ptr = opendir(path);
	found = 0;
	if (!dir_ptr)
		return (errno = ENOENT, errno);
	while (1)
	{
		dir_entity = readdir(dir_ptr);
		if (!dir_entity)
			break ;
		if (!ft_strcmp(dir_entity->d_name, cmd_name))
		{
			found = 1;
			ft_printf("Found in path %s\n", path);
			break ;
		}
	}
	closedir(dir_ptr);
	if (!found)
		return (0);
	return (1);
}
