/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:58:47 by uschmidt          #+#    #+#             */
/*   Updated: 2025/04/08 13:38:55 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

/*
within exe the signalhandler is replaces and set back before returning from exe
*/

void	handle_exe_interupt(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 2);
		return ;
	}
	else if (sig == SIGQUIT)
	{
		write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
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
	//struct sigaction old_INT;
	//struct sigaction old_QUIT;

	//app->sa.sa_handler = &handle_exe_interupt;
	//app->sa.sa_flags = 0;
	//sigemptyset(&app->sa.sa_mask);
	
	//sigaction(SIGINT, NULL, &old_INT);
	/*sigaction(SIGINT, &app->sa, NULL);

	struct sigaction sa_quit;
	sa_quit.sa_handler = &handle_exe_interupt;
    sa_quit.sa_flags = 0;
 	sigemptyset(&sa_quit.sa_mask);
 	sigaction(SIGQUIT, NULL, &old_QUIT);
	sigaction(SIGQUIT, &sa_quit, NULL);	
*/
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
	//sigaction(SIGINT, &old_INT, NULL);
	//sigaction(SIGQUIT, &old_QUIT, NULL);
	return (err);
}
