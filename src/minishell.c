/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:27:39 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/27 17:21:19 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char **argv, char *envp[])
{
	t_app	*app;

	if (argc != 1 || !argv)
		return (1);
	//errorhandling
	app = init_shell(envp);
	start_shell(app);
	//TODO: controlled exit on SIGTER...);
	free(app);
	return (0);
}
