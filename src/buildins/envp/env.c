/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:41:06 by jhelbig           #+#    #+#             */
/*   Updated: 2025/05/02 11:33:42 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	env(t_app *app, t_cmd_info *cmd)
{
	int	i;

	i = 0;
	reroute_io(cmd->infile, cmd->outfile);
	while (cmd && app->envp[i])
	{
		if (ft_strchr(app->envp[i], '=') != NULL)
			ft_printf("%s\n", app->envp[i]);
		i++;
	}
	if (cmd->infile != 0)
		close(cmd->infile);
	if (cmd->outfile != 1)
		close(cmd->outfile);
	return (0);
}

char	*get_env_val(t_app *app, char *key)
{
	int		i;
	int		len;

	len = ft_strlen(key);
	i = 0;
	while (app->envp[i])
	{
		if (!ft_strncmp(app->envp[i], key, len))
			return (ft_strdup(app->envp[i] + len + 1));
		i++;
	}
	return (NULL);
}
