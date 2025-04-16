/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:03:56 by uschmidt          #+#    #+#             */
/*   Updated: 2025/04/10 15:18:58 by jhelbig          ###   ########.fr       */
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
/*	
	int i = 0;
	while (app->envp[i])
	{
		ft_printf("%s\n", app->envp[i]);
		i++;
	}
*/	
	app->prompt = NULL;
	return (app);
}
