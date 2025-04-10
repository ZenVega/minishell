/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:03:56 by uschmidt          #+#    #+#             */
/*   Updated: 2025/04/10 15:07:45 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "../malloc_list/malloc_list.h"

char	**copy_envp(char **envp, t_list **malloc_list)
{
	int		size;
	int		i;
	char	**copy;

	size = 0;
	while (envp[size])
		size++;
	copy = malloc_and_add_list(malloc_list, sizeof(char *) * size + 1);
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		add_to_malloc_list(malloc_list, copy[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

t_app	*init_shell(char *envp[])
{
	t_app	*app;

	app = (t_app *)malloc(sizeof(t_app));
	if (!app)
		return (NULL);
	app->malloc_list = NULL;
	app->envp = copy_envp(envp, &app->malloc_list);
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
