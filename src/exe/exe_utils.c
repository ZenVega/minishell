/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:00:35 by uschmidt          #+#    #+#             */
/*   Updated: 2025/04/28 10:47:12 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

void	*free_paths(t_cmd_info *cmd, char **paths, int len, char *cmd_name)
{
	free(cmd_name);
	while (--len >= 0)
	{
		free(paths[len]);
		paths[len] = NULL;
	}
	free(paths);
	set_err(cmd, ERR_MALLOC, NULL);
	return (NULL);
}

int	get_paths_len(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		i++;
	return (i);
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
	return (0);
}
