/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:56:09 by jhelbig           #+#    #+#             */
/*   Updated: 2025/04/08 13:56:14 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

//handling SIGINT to just display a newline
void	handle_signal_shell(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_sa_shell(t_app *app)
{
	app->sa_init.sa_handler = &handle_signal_shell;
	app->sa_init.sa_flags = 0;
	sigemptyset(&app->sa_init.sa_mask);
	sigaction(SIGINT, &app->sa_init, NULL);	
	
	app->sa_quit.sa_handler = SIG_IGN;  // Ignore SIGTERM for the shell
    app->sa_quit.sa_flags = 0;
    sigemptyset(&app->sa_quit.sa_mask);
    sigaction(SIGQUIT, &app->sa_quit, NULL); 
}
