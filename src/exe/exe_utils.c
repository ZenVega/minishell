/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:00:35 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/19 11:06:56 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

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
		return (errno = ENOENT, errno);
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
