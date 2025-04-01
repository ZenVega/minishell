/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:29:31 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/27 15:54:54 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <errno.h>
# include <stdio.h>
# include <string.h>
# include "../libft/libft.h"

int		is_space(char c);
void	exit_with_error(char *cmd_name);
void	*free_list(char **list);
char	**dup_str_arr(char **arr);
#endif
