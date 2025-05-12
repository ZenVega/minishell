/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_get_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:12:24 by uschmidt          #+#    #+#             */
/*   Updated: 2025/04/28 12:55:37 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

static int	has_access_ret(t_app *app, t_cmd_info *cmd, char *path)
{
	struct stat	sb;

	stat(path, &sb);
	if ((sb.st_mode & S_IFMT) == S_IFDIR)
		return (app->ret_val = 126, set_err(cmd, ERR_IS_FOLDER, path));
	if (access(path, R_OK))
		return (app->ret_val = 127, set_err(cmd, ERR_NO_FILE, path));
	if (access(path, X_OK))
		return (app->ret_val = 126, set_err(cmd, ERR_PERM, path));
	return (0);
}

static char	**add_cmd_name(t_cmd_info *cmd, char *cmd_name,
		int path_len, char **paths)
{
	char	*tmp;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], cmd_name);
		if (!tmp)
			return (free_paths(cmd, paths, path_len, cmd_name));
		free(paths[i]);
		paths[i] = tmp;
		i++;
	}
	return (paths);
}

static char	**get_paths_from_env(t_app *app, t_cmd_info *cmd, char *cmd_name)
{
	int		path_len;
	char	**paths;
	char	*tmp;

	tmp = get_env_val(app, "PATH");
	if (!tmp)
		return (set_err(cmd, ERR_NO_VAR, "PATH"), NULL);
	add_to_malloc_list(&app->malloc_list, tmp);
	cmd_name = ft_strjoin("/", cmd_name);
	if (!cmd_name)
		return (set_err(cmd, ERR_MALLOC, NULL), NULL);
	paths = ft_split(tmp, ':');
	if (!paths)
		return (set_err(cmd, ERR_MALLOC, NULL), NULL);
	path_len = get_char_arr_len(paths);
	paths = add_cmd_name(cmd, cmd_name, path_len, paths);
	free(cmd_name);
	return (paths);
}

char	*filter_paths(t_app *app, t_cmd_info *cmd, char **paths)
{
	int		found;
	char	*path;

	found = 0;
	path = NULL;
	while (*paths)
	{
		if (!found && !has_access_ret(app, cmd, *paths))
		{
			found = 1;
			path = *paths;
			add_to_malloc_list(&app->malloc_list, *paths);
		}
		else
			free(*paths);
		paths++;
	}
	if (!path)
		return (app->ret_val = 127, set_err(cmd, ERR_NO_CMD, path), NULL);
	return (path);
}

char	*get_path(t_cmd_info *cmd, t_exe *exe, t_app *app)
{
	char	**paths;

	if (exe->cmd_name[0] == '/' || exe->cmd_name[0] == '.')
		if (!has_access_ret(app, cmd, exe->cmd_name))
			return (exe->cmd_name);
		else
			return (NULL);
	else
	{
		paths = get_paths_from_env(app, cmd, exe->cmd_name);
		if (!paths)
			return (set_err(cmd, ERR_MALLOC, NULL), NULL);
		add_to_malloc_list(&app->malloc_list, paths);
		return (filter_paths(app, cmd, paths));
	}
	return (NULL);
}
