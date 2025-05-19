/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:53:37 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/19 15:18:16 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "echo.h"

int	echo(t_app *app, t_cmd_info *cmd)
{
	int		i;
	int		j;
	int		new_line;
	char	**args;

	new_line = 1;
	i = 0;
	j = 1;
	if (!app)
		return (0);
	args = cmd->args + 1;
	while (*args && (*args)[0] == '-')
	{
		while ((*args)[j] == 'n')
			j++;
		if ((*args)[j] == '\0')
		{
			new_line = 0;
			args++;
			j = 1;
		}
		else
			break ;
	}
	while (args[i])
	{
		if (args[i + 1])
			ft_fprintf(cmd->outfile, "%s ", args[i++]);
		else
			ft_fprintf(cmd->outfile, "%s", args[i++]);
	}
	if (new_line)
		ft_fprintf(cmd->outfile, "\n");
	return (0);
}
