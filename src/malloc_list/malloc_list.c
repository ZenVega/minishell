/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:57:04 by jhelbig           #+#    #+#             */
/*   Updated: 2025/03/19 09:28:39 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_list.h"

//to be used instead of malloc
void	*malloc_and_add_list(t_list **malloc_list, size_t size)
{
	void	*addr;
	t_list	*new_node;

	addr = malloc(size);
	if (!addr)
		return (NULL);
	new_node = ft_lstnew(addr);
	ft_lstadd_back(malloc_list, new_node);
	return (addr);
}

//if another function does malloc
void	add_to_malloc_list(t_list **malloc_list, void *addr)
{
	t_list	*new_node;

	new_node = ft_lstnew(addr);
	ft_lstadd_back(malloc_list, new_node);
}

void	add_list_to_malloc_list(t_list **malloc_list, void **addr)
{
	void	**og_addr;

	og_addr = addr;
	while (*addr)
	{
		add_to_malloc_list(malloc_list, *addr);
		addr++;
	}
	add_to_malloc_list(malloc_list, og_addr);
}

// to free the list call:
// ft_lstclear(**malloc_list, free)
void	free_malloc_list(t_app *app)
{
	ft_lstclear(&app->malloc_list, free);
	free(app->malloc_list);
}
