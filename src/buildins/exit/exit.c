/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:05:26 by jhelbig           #+#    #+#             */
/*   Updated: 2025/04/28 10:48:32 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"

void	free_comp_app(t_app *app)
{
	free_malloc_list(app);
	free_var_arr(app->envp);
	free_var_arr(app->local_var);
	free(app->prompt);
	free(app);
}

int	ft_exit(t_app *app, t_cmd_info *cmd)
{
	int		err;
	char	*suspect;

	reroute_io(cmd->infile, cmd->outfile);
	err = 0;
	if (cmd->args[1])
	{
		if (cmd->args[2])
		{
			err = 1;
			set_err(cmd, 101, "exit");
			return (err);
		}
		else if (!ft_isnumber(cmd->args[1]))
		{
			err = 2;
			suspect = ft_strjoin("exit: ", cmd->args[1]);
			add_to_malloc_list(&app->malloc_list, suspect);
			set_err(cmd, 102, suspect);
			exit_with_error(*cmd);
		}
		else
			err = ft_atoi(cmd->args[1]) % 256;
	}
	if (cmd->infile != 0)
		close(cmd->infile);
	if (cmd->outfile != 1)
		close(cmd->outfile);
	free_comp_app(app);
	ft_fprintf(STDOUT_FILENO, "exit\n");
	exit(err);
}
