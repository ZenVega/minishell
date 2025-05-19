/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:00:35 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/19 14:05:36 by uschmidt         ###   ########.fr       */
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

int	has_access_ret(t_app *app, t_cmd_info *cmd, char *path)
{
	struct stat	sb;

	stat(path, &sb);
	if ((sb.st_mode & S_IFMT) == S_IFDIR)
		return (app->ret_val = 126, set_err(cmd, ERR_IS_FOLDER, path));
	else if (access(path, F_OK))
		return (app->ret_val = 127, set_err(cmd, ERR_NO_FILE, path));
	else if (access(path, X_OK))
		return (app->ret_val = 126, set_err(cmd, ERR_PERM, path));
	return (0);
}
