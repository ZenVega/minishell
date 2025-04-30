/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:03:56 by uschmidt          #+#    #+#             */
/*   Updated: 2025/04/30 09:56:00 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "../malloc_list/malloc_list.h"
#include "../utils/utils.h"

t_app	*init_shell(char *envp[])
{
	t_app	*app;

	app = (t_app *)malloc(sizeof(t_app));
	if (!app)
		return (NULL);
	app->malloc_list = NULL;
	app->envp = copy_envp(envp);
	if (!app->envp)
		return (NULL);
	app->prompt = NULL;
	app->ret_val = 0;
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
