/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:03:56 by uschmidt          #+#    #+#             */
/*   Updated: 2025/04/23 09:06:04 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

char	**copy_envp(char **envp, t_list **malloc_list)
{
	int		size;
	int		i;
	char	**copy;

	malloc_list = NULL;
	size = 0;
	while (envp[size])
		size++;
	copy = (char **)malloc(sizeof(char *) * (size + 1));
	if (!copy);
		return (NULL);
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
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
	if (!app->envp)
		return (NULL);
	app->prompt = NULL;
	return (app);
}
