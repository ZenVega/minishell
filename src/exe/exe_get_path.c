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
		if (!paths[i])
			return (free_paths(cmd, paths, path_len, cmd_name));
		i++;
	}
	return (paths);
}

char	**get_paths_from_env(t_cmd_info *cmd, char *cmd_name)
{
	int		path_len;
	char	**paths;
	char	*tmp;

	tmp = getenv("PATH");
	if (!tmp)
		return (set_err(cmd, ERR_NO_VAR, "PATH"), NULL);
	cmd_name = ft_strjoin("/", cmd_name);
	if (!cmd_name)
		return (set_err(cmd, ERR_MALLOC, NULL), NULL);
	paths = ft_split(tmp, ':');
	if (!paths)
		return (set_err(cmd, ERR_MALLOC, NULL), NULL);
	path_len = get_paths_len(paths);
	paths = add_cmd_name(cmd, cmd_name, path_len, paths);
	free(cmd_name);
	return (paths);
}

static int	clean_cmd_name(t_cmd_info *cmd, char **cmd_name)
{
	int		len;
	char	*tmp;

	len = ft_strlen(*cmd_name) - 1;
	while (len >= 0 && (*cmd_name)[len] != '/')
		len--;
	if (len == -1)
	{
		*cmd_name = NULL;
		return (1);
	}
	tmp = ft_strdup(*cmd_name + len + 1);
	if (!tmp)
		return (set_err(cmd, ERR_MALLOC, NULL));
	*cmd_name = tmp;
	return (0);
}

//is absolute path
//is relative path
//is plain cmd
char	*get_path(t_cmd_info *cmd, t_exe *exe, t_app *app)
{
	char	**paths;
	char	*path;
	int		found;

	found = 0;
	if (exe->cmd_name[0] == '/' || exe->cmd_name[0] == '.')
	{
		clean_cmd_name(cmd, &exe->args[0]);
		return (exe->cmd_name);
	}
	else
	{
		paths = get_paths_from_env(cmd, exe->cmd_name);
		if (!paths)
			return (NULL);
		add_to_malloc_list(&app->malloc_list, paths);
		while (*paths)
		{
			if (!found && !access(*paths, X_OK))
			{
				found = 1;
				path = *paths;
				add_to_malloc_list(&app->malloc_list, *paths);
			}
			else
				free(*paths);
			paths++;
		}
		return (path);
	}
	return (NULL);
}
