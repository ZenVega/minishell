/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:10:59 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/23 12:13:49 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

void	init_signal_hd_parent(t_app *app)
{
	app->sa_int.sa_handler = SIG_IGN;
	sigaction(SIGINT, &app->sa_int, NULL);
}

static void	handle_signal_hd_child(int sig)
{
	int	fd;

	if (sig == SIGINT)
	{
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
