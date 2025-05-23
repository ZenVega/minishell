/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:19:06 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/13 14:53:41 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

t_buildin	is_buildin(char *cmd)
{
	char	*buildins[BI_COUNT];
	int		i;

	buildins[BI_ECHO] = "echo";
	buildins[BI_CD] = "cd";
	buildins[BI_PWD] = "pwd";
	buildins[BI_EXPORT] = "export";
	buildins[BI_UNSET] = "unset";
	buildins[BI_ENV] = "env";
	buildins[BI_EXIT] = "exit";
	buildins[7] = NULL;
	i = 0;
	while (buildins[i])
	{
		if (!ft_strcmp(cmd, buildins[i]))
			return (i);
		i++;
	}
	return (BI_NULL);
}

int	exe_buildin(t_app *app, t_cmd_info *cmd)
{
	t_buildin	bi_cmd;
	int			err;

	err = BI_NULL;
	bi_cmd = is_buildin(cmd->args[0]); 
	if (bi_cmd == BI_NULL)
		return (err);
	else if (bi_cmd == BI_CD)
		err = cd(app, cmd);
	else if (bi_cmd == BI_ECHO)
		err = echo(app, cmd);
	else if (bi_cmd == BI_ENV)
		err = env(app, cmd);
	else if (bi_cmd == BI_EXIT)
		err = ft_exit(app, cmd);
	else if (bi_cmd == BI_PWD)
		err = pwd(app, cmd);
	else if (bi_cmd == BI_UNSET)
		err = unset_var(app, cmd);
	app->ret_val = err;
	if (bi_cmd == BI_EXPORT)
		err = ft_export(app, cmd);
	return (err);
}
