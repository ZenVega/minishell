/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:03:56 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/25 15:52:47 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

t_app	*init_shell(char *envp[])
{
	t_app	*app;

	app = (t_app *)malloc(sizeof(t_app));
	if (!app)
		return (NULL);
	app->malloc_list = NULL;
	app->envp = envp;
	app->prompt = NULL;
	return (app);
}

t_parser_info	init_parser_info(int infile, int outfile, char *line)
{
	t_parser_info	p_info;

	p_info.infile = infile;
	p_info.outfile = outfile;
	p_info.line = line;
	p_info.mask = NULL;
	return (p_info);
}
