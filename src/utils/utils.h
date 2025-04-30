/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:29:31 by uschmidt          #+#    #+#             */
/*   Updated: 2025/04/28 11:52:07 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../libft/libft.h"
# include "../includes/types.h"

int		is_space(char c);
char	**copy_and_qsort(char **array);
char	**copy_envp(char **envp);
int		get_char_arr_len(char **paths);
void	reroute_io(int input, int output);

#endif
