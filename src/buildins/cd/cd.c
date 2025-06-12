/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:31:28 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/19 15:39:08 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

static int	update_pwd(t_app *app, char *new_path)
{
	char	*old_pwd;
	int		err;

	err = 0;
	old_pwd = get_env_val(app, "PWD");
	err = update_or_add_var("OLDPWD", old_pwd, app);
	free(old_pwd);
	if (err)
		return (err);
	err = update_or_add_var("PWD", new_path, app);
	if (err)
		return (err);
	return (0);
}

static char	*add_to_home_route(t_app *app, char *path)
{
	char	*tmp;
	char	*abs_path;

	tmp = get_home_path(app);
	if (!tmp)
		return (NULL);
	if (path == NULL)
		return (tmp);
	abs_path = (char *)malloc_and_add_list(&app->malloc_list, sizeof(char)
			* (ft_strlen(tmp) + ft_strlen(path) + 1));
	abs_path = ft_strjoin(tmp, path + 1);
	if (!abs_path)
		return (free(tmp), NULL);
	ft_printf("%s\n", abs_path);
	return (add_to_malloc_list(&app->malloc_list, abs_path), abs_path);
}

static char	*get_abs_path(t_app *app, char *path)
{
	char	*cur_path;

	if (path == NULL || !ft_strncmp("~\0", path, 2))
		return (add_to_home_route(app, NULL));
	if (path[0] == '/')
		return (path);
	cur_path = get_env_val(app, "PWD");
	add_to_malloc_list(&app->malloc_list, cur_path);
	if (!ft_strncmp("~/", path, 2))
		return (add_to_home_route(app, path));
	if (!ft_strncmp("-\0", path, 2))
	{
		cur_path = get_env_val(app, "OLDPWD");
		add_to_malloc_list(&app->malloc_list, cur_path);
		return (cur_path);
	}
	return (path);
}

int	cd(t_app *app, t_cmd_info *cmd)
{
	char	*abs_path;

	if (!cmd->args[1])
		return (0);
	if (get_char_arr_len(cmd->args) > 2)
		return (set_err(cmd, ERR_MANY_ARGS, "cd"), 1);
	abs_path = get_abs_path(app, cmd->args[1]);
	if (abs_path == NULL)
		return (set_err(cmd, ERR_NO_FILE, "cd"));
	if (folder_access(app, cmd, abs_path, cmd->args[1]))
		return (1);
	if (!chdir(abs_path))
	{
		if (update_pwd(app, abs_path))
			return (set_err(cmd, ERR_NO_FILE, "cd"));
		return (0);
	}
	return (set_err(cmd, ERR_NO_FILE, cmd->args[1]), 1);
}
