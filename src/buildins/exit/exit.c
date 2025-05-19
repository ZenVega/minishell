/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:05:26 by jhelbig           #+#    #+#             */
/*   Updated: 2025/05/19 18:18:08 by jhelbig          ###   ########.fr       */
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

//err status is only an 8bit integer, result is truncated to be between 0-255
int	ft_exit(t_app *app, t_cmd_info *cmd)
{
	int		err;
	char	*suspect;

	err = 0;
	if (cmd->args[1])
	{
		if (cmd->args[2])
			return (set_err(cmd, ERR_MANY_ARGS, "exit"), 1);
		else if (!ft_isnumber(cmd->args[1]))
		{
			err = 2;
			suspect = ft_strjoin("exit: ", cmd->args[1]);
			add_to_malloc_list(&app->malloc_list, suspect);
			set_err(cmd, ERR_NUM_ARGS, suspect);
			exit_with_error(*cmd);
		}
		else
			err = ft_atoi(cmd->args[1]) % 256;
	}
	if (cmd->infile == STDIN_FILENO && cmd->outfile == STDOUT_FILENO)
		write(STDERR_FILENO, "exit\n", 5);
	if (cmd->outfile != STDOUT_FILENO)
		close(cmd->outfile);
	if (cmd->infile != STDIN_FILENO)
		close(cmd->infile);
	free_comp_app(app);
	exit(err);
}
