/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:10:59 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/23 12:41:11 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

void	disable_ctrl_c_echo(int activate) 
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	if (activate)
		term.c_lflag &= ~ECHOCTL;
	else
		term.c_lflag &= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

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
		g_global_signal = ERR_SIGINT;
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

void	handle_signals(t_heredoc *hd, char *next_line)
{
	if (g_global_signal == ERR_SIGINT)
	{
		unlink(hd->doc_name);
		close(hd->fd);
		write(2, "^C\n", 3);
		g_global_signal = 0;
		exit(ERR_SIGINT);
	}
	if (next_line == NULL)
	{
		write(STDOUT_FILENO, "minishell: warning: here-document delimited by end-of-file (wanted ", 67);
		write(STDOUT_FILENO, hd->del, ft_strlen(hd->del));
		write(STDOUT_FILENO, ")\n", 2);
		close(hd->fd);
		exit (0);
	}
}
