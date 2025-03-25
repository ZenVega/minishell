/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:42:12 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/25 16:03:10 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	start_shell(t_app *app)
{
	char	*read_line;
	//TODO: create prompt
	while (1)
	{
		read_line = readline(app->prompt);
		// FORK -> EXE(PARSER(read_line)):
		// cleanup
		ft_printf("%s\n", read_line);
		free(read_line);
	}
}
