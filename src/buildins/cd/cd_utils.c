/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:59:01 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/02 15:12:39 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

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
	ft_strlcat(home_path, "/home/", 7);
	ft_strlcat(home_path, tmp, ft_strlen(tmp) + 7);
	free(tmp);
	return (home_path);
}
