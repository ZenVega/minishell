/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:53:37 by uschmidt          #+#    #+#             */
/*   Updated: 2025/04/25 14:24:20 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "echo.h"

int	echo(t_app *app, t_cmd_info *cmd)
{
	int		err;
	int		i;
	int		new_line;
	char	**args;

	err = 0;
	new_line = 1;
	i = 0;
	if (!app)
		return (err);
	args = cmd->args + 1;
	if (*args && !ft_strcmp(*args, "-n"))
	{
		args++;
		new_line = 0;
	}
	while (args[i])
	{
		if (args[i + 1])
			ft_printf("%s ", args[i++]);
		else
			ft_printf("%s", args[i++]);
	}
	if (new_line)
		ft_printf("\n");
	return (err);
}
