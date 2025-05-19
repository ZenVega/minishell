/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:59:01 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/19 15:50:32 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

int	folder_access(t_app *app, t_cmd_info *cmd, char *path, char *og_path)
{
	struct stat	sb;
	char		*subject;

	subject = ft_strjoin("cd: ", og_path);
	add_to_malloc_list(&app->malloc_list, subject);
	stat(path, &sb);
	if (access(path, F_OK))
		return (app->ret_val = 127, set_err(cmd, ERR_NO_FILE, subject));
	else if (!((sb.st_mode & S_IFMT) == S_IFDIR))
		return (app->ret_val = 1, set_err(cmd, ERR_IS_NO_FOLDER, subject));
	else if (access(path, X_OK))
		return (app->ret_val = 126, set_err(cmd, ERR_PERM, subject));
	return (0);
}

int	remove_last_route(char **path)
{
	int	len;

	len = ft_strlen(*path);
	while (len >= 0 && (*path)[len] != '/')
		(*path)[len--] = 0;
	if (len >= 0 && (*path)[len] == '/')
		return ((*path)[len] = 0, 0);
	return (-1);
}

char	*get_home_path(t_app *app)
{
	char	*tmp;
	char	*home_path;

	tmp = get_env_val(app, "USER");
	if (!tmp)
		return (NULL);
	home_path = (char *)malloc(sizeof(char) * (ft_strlen(tmp) + 7));
	if (!home_path)
		return (free(tmp), NULL);
	ft_strlcpy(home_path, "/home/", 7);
	ft_strlcat(home_path, tmp, ft_strlen(tmp) + 7);
	free(tmp);
	return (home_path);
}
