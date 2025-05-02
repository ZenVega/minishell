/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:31:28 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/02 11:41:49 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

static int remove_last_route(char **path)
{
	int len;

	len = ft_strlen(*path);
	while (len >= 0 && (*path)[len] != '/')
		(*path)[len--] = 0;
	if (len >=0 && (*path)[len] =='/')
		return ((*path)[len] = 0, 0);
	return (-1);
}

static char	*get_abs_path(t_app *app, char *path)
{
	char *abs_path;
	char *cur_path;

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
	if (path[0] == '.')
		if (path[1] ==
	return (path);
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
	if (get_char_arr_len(cmd->args) != 2)
		return (set_err(cmd, ERR_NUM_ARGS, "cd"));
	abs_path = get_abs_path(app, cmd->args[1]);
	if (abs_path == NULL)
		return (set_err(cmd, ERR_NO_FILE, "cd"));

	chdir(abs_path);
	return (0);
}
