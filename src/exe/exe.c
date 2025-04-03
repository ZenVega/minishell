/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:58:47 by uschmidt          #+#    #+#             */
/*   Updated: 2025/04/03 13:40:11 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

void	handle_exe_interupt(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 2);
		return ;
	}
}

// exe takes the cmd struct
// checks if the input is valid
// and executes the corresponding function
// if there is an err, we exit cleanly
int	exe(t_app *app, t_cmd_info *cmd)
{
	int	err;
	struct sigaction old_sa;

	app->sa.sa_handler = &handle_exe_interupt;
	app->sa.sa_flags = 0;
	sigemptyset(&app->sa.sa_mask);
	
	sigaction(SIGINT, NULL, &old_sa);
	sigaction(SIGINT, &app->sa, NULL);
	err = is_valid(cmd);
	if (err)
		return (err);
//		on_error();
	if (cmd->type == BIN)
		err = exe_bin(app, cmd);
	else if (cmd->type == PIPE)
		err = open_pipe(app, cmd);
	//TODO: CLEANUP 
	if (err)
		exit_with_error(cmd->args[0]);
	sigaction(SIGINT, &old_sa, NULL);
	return (err);
}
