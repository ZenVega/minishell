/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:56:09 by jhelbig           #+#    #+#             */
/*   Updated: 2025/05/21 10:10:25 by jhelbig          ###   ########.fr       */
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
		g_global_signal = ERR_SIG;
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	else if (sig == SIGQUIT)
	{
		g_global_signal = 131;
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

void	handle_signal_hd_parent(int sig)
{
	if (sig == SIGINT)
	{
		g_global_signal = ERR_SIG;  // Set a global flag
		write(STDOUT_FILENO, " ^D\n", 4);
	}
}

void	init_signal_hd_parent(t_app *app)
{
	sigemptyset(&app->sa_int.sa_mask);
	app->sa_int.sa_flags = 0;
	app->sa_int.sa_handler = SIG_IGN;
	//app->sa_int.sa_handler = &handle_signal_hd_parent;
	sigaction(SIGINT, &app->sa_int, NULL);
}

void	handle_signal_hd_child(int sig)
{
	int	fd;

	ft_printf("SIGINT handler");
	if (sig == SIGINT)
	{
		ft_printf("SIGINT in child");
		g_global_signal = ERR_SIG;
		fd = open("/dev/null", O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

void	init_signal_hd_child(t_app *app)
{
	app->sa_int.sa_handler = &handle_signal_hd_child;
	sigaction(SIGINT, &app->sa_int, NULL);
}
