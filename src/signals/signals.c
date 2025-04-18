/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:56:09 by jhelbig           #+#    #+#             */
/*   Updated: 2025/04/08 15:04:16 by jhelbig          ###   ########.fr       */
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
	app->sa_int.sa_handler = &handle_signal_shell;
	app->sa_int.sa_flags = 0;
	sigemptyset(&app->sa_int.sa_mask);
	sigaction(SIGINT, &app->sa_int, NULL);	
	
	app->sa_quit.sa_handler = SIG_IGN;
    app->sa_quit.sa_flags = 0;
    sigemptyset(&app->sa_quit.sa_mask);
    sigaction(SIGQUIT, &app->sa_quit, NULL); 
}

void	handle_signal_parent(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	else if (sig == SIGQUIT)
	{
		write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
		return ;
	}
}

void	init_sa_parent(t_app *app)
{
	app->sa_int.sa_handler = &handle_signal_parent;
	sigaction(SIGINT, &app->sa_int, NULL);

	app->sa_quit.sa_handler = &handle_signal_parent;
	sigaction(SIGQUIT, &app->sa_quit, NULL);
}

void	init_sa_child(t_app *app)
{
	app->sa_int.sa_handler = SIG_DFL;
	sigaction(SIGINT, &app->sa_int, NULL);

	app->sa_quit.sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &app->sa_quit, NULL);	
}
