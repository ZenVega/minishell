/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:24:17 by uschmidt          #+#    #+#             */
/*   Updated: 2025/04/10 15:38:43 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_LIST_H
# define MALLOC_LIST_H

# include "../libft/libft.h"
# include "../includes/types.h"

void	*malloc_and_add_list(t_list **malloc_list, size_t size);
void	add_to_malloc_list(t_list **malloc_list, void *addr);
void	add_list_to_malloc_list(t_list **malloc_list, void **addr);
void	free_malloc_list(t_app *app);
void	free_envp(char **envp);

#endif
