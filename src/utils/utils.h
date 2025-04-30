/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:29:31 by uschmidt          #+#    #+#             */
/*   Updated: 2025/04/30 11:12:13 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../libft/libft.h"
# include "../includes/types.h"
# include "../malloc_list/malloc_list.h"

char	**copy_and_qsort(char **array);
char	**copy_envp(char **envp);
int		is_space(char c);
void	reroute_io(int input, int output);

#endif
