/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:05:26 by jhelbig           #+#    #+#             */
/*   Updated: 2025/04/23 08:38:15 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"

void	free_comp_app(t_app *app)
{
	free_malloc_list(app);
	free_envp(app->envp);
	free(app->prompt);
	free(app);
}

int	ft_exit(t_app *app, t_cmd_info *cmd)
{
	int	err;
	
	reroute_io(cmd->infile, cmd->outfile);
	ft_fprintf(STDERR_FILENO, "exit\n");
	err = 0;
	if (cmd->args[1])
	{	
		if (cmd->args[2])
		{
			err = 1;
			ft_fprintf(2, "minishell: exit: too many arguments\n");
		}
		else if (!ft_isnumber(cmd->args[1]))
		{
			err = 2;
			ft_fprintf(2, "minishell: exit: %s: numeric argument requiered\n", 
				cmd->args[1]);
		}
		else
			err = ft_atoi(cmd->args[1]);
	}
	if (cmd->infile != 0)
		close(cmd->infile);
	if (cmd->outfile != 1)
		close(cmd->outfile);
	free_comp_app(app);
	exit(err);
	return (err);
}
