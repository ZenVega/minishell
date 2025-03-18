/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:57:04 by jhelbig           #+#    #+#             */
/*   Updated: 2025/03/18 13:29:04 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*add_malloc_list(t_list **malloc_list, size_t size)
{
	void	*addr;
	t_list	*new_node;

	addr = malloc(size);	
	new_node = ft_lstnew(addr);
	ft_lstadd_back(malloc_list, new_node);
	return (addr);
}

// to free the list call:
// ft_lstclear(**malloc_list, free)
