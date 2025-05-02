/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:31:28 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/02 15:12:43 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

//static void	update_pwd(t_app *app, char *new_path)
//{
//}

static char	*add_to_home_route(t_app *app, char *path)
{
	char	*tmp;
	char	*abs_path;

	tmp = get_home_path(app);
	if (!tmp)
		return (NULL);
	if (path == NULL)
		return (tmp);
	abs_path = ft_strjoin(tmp, path + 1);
	if (!abs_path)
		return (free(tmp), NULL);
	return (add_to_malloc_list(&app->malloc_list, abs_path), abs_path);
}

static char	*add_to_path(t_app *app, char *cur_path, char *new_path)
{
	char	*abs_path;
	int		len_cur_path;

	len_cur_path = ft_strlen(cur_path);
	if (!ft_strncmp("./", new_path, 2))
		return (ft_strjoin(cur_path, new_path + 1));
	abs_path = (char *)malloc_and_add_list(&app->malloc_list, sizeof(char)
			* (len_cur_path + ft_strlen(new_path) + 2));
	if (!abs_path)
		return (NULL);
	ft_strlcat(abs_path, cur_path, len_cur_path + 1);
	ft_strlcat(abs_path + len_cur_path, "/", ft_strlen(abs_path) + 2);
	ft_strlcat(abs_path + len_cur_path + 1, new_path,
		ft_strlen(abs_path) + ft_strlen(new_path) + 1);
	return (abs_path);
}

static char	*get_abs_path(t_app *app, char *path)
{
	char	*cur_path;

	if (path == NULL)
		return (add_to_home_route(app, NULL));
	if (path[0] == '/')
		return (path);
	cur_path = get_env_val(app, "PWD");
	add_to_malloc_list(&app->malloc_list, cur_path);
	while (!ft_strncmp("../", path, 3))
	{
		path += 3;
		if (remove_last_route(&cur_path))
			return (NULL);
	}
	if (!ft_strncmp("~/", path, 2))
		return (add_to_home_route(app, path));
	if (!ft_strncmp("..", path, 2) && path[2] == '\0')
	{
		if (remove_last_route(&cur_path))
			return (NULL);
		else
			return (cur_path);
	}
	return (add_to_path(app, cur_path, path));
}

// set OLDPWD as current PWD
// get 'directory value'
// expand args / clean string
// set PWD
// updateprompt if necessary
int	cd(t_app *app, t_cmd_info *cmd)
{
	char	*abs_path;

	if (!app)
		return (-1);
	if (get_char_arr_len(cmd->args) > 2)
		return (set_err(cmd, ERR_NUM_ARGS, "cd"));
	abs_path = get_abs_path(app, cmd->args[1]);
	if (abs_path == NULL)
		return (set_err(cmd, ERR_NO_FILE, "cd"));
	if (!chdir(abs_path))
	{
		//update_pwd(app, abs_path);
		return (0);
	}
	return (1);
}
