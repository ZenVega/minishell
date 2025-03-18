/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:24:17 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/18 16:52:06 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_LIST_H
# define MALLOC_LIST_H

# include "../includes/minishell.h"
# include "../libft/libft.h"

void	*malloc_and_add_list(t_list **malloc_list, size_t size);
void	add_to_malloc_list(t_list **malloc_list, void *addr);
void	free_malloc_list(t_app *app);

#endif
