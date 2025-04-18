/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:27:39 by uschmidt          #+#    #+#             */
/*   Updated: 2025/04/03 11:02:51 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char **argv, char *envp[])
{
	t_app				*app;
	
	if (argc != 1 || !argv)
	{
		write(2, "Invalid arguments\n", 18);
		return (-1);
	}
	app = init_shell(envp);
	if (app == NULL)
		return (-1);
	start_shell(app);
	free(app);
	return (0);
}
