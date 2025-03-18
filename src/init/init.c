/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:03:56 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/18 16:42:53 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

t_app	*init_shell(char *envp[])
{
	t_app	*app;
	char	*test;

	app = (t_app *)malloc(sizeof(t_app));
	if (!app)
		return (NULL);
	//error handling here
	app->malloc_list = NULL;
	app->envp = envp;
	test = malloc_and_add_list(&app->malloc_list, (sizeof(char) * 5));
	test[0] = 'H';
	while (0 && *envp)
	{
		ft_printf("%s\n", *envp);
		envp++;
	}
	return (app);
}
