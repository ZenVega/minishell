/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:38:09 by uschmidt          #+#    #+#             */
/*   Updated: 2025/04/08 15:21:12 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pwd.h"

char	*get_cwd(void)
{
	char	*path_abs;
	int		i;

	i = 1;
	path_abs = NULL;
	while (path_abs == NULL)
	{
		free(path_abs);
		path_abs = (char *)malloc(BUFFER_SIZE * i);
		if (!path_abs)
			return (NULL);
		path_abs = getcwd(path_abs, BUFFER_SIZE * i);
		i++;
	}
	return (path_abs);
}
int	pwd(t_app *app, t_cmd_info *cmd)
{
	char	*path_abs;

	if (!app || ! cmd)
		return (-1);
	path_abs = get_cwd();
	if (!path_abs)
		return (set_err(cmd, ERR_MALLOC, NULL));
	ft_printf("%s\n", path_abs);
	free(path_abs);
	return (0);
}
