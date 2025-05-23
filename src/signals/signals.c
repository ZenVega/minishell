/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:56:09 by jhelbig           #+#    #+#             */
/*   Updated: 2025/05/23 12:39:38 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

int	g_global_signal;

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
	g_global_signal = 0;
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
		g_global_signal = ERR_SIGINT;
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	else if (sig == SIGQUIT)
	{
		g_global_signal = ERR_SIGTER;
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
