/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:27:39 by uschmidt          #+#    #+#             */
/*   Updated: 2025/04/02 12:27:22 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
/*
int handle_signal(int sig)
{
	if (sig = SIGQUIT)
		return (0);
}
*/

int	main(int argc, char **argv, char *envp[])
{
	t_app				*app;
	
	if (argc != 1 || !argv)
		return (1);
	app = init_shell(envp);
	start_shell(app);
	//TODO: controlled exit on SIGTER...);
	free(app);
	return (0);
}
