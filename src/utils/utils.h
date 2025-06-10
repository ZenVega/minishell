/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:29:31 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/13 16:32:47 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../error/error.h"
# include "../includes/types.h"
# include "../libft/libft.h"
# include "../malloc_list/malloc_list.h"
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

int		is_space(char c);
char	**copy_and_qsort(char **array);
char	**copy_envp(char **envp);
int		get_char_arr_len(char **paths);
void	reroute_io(t_cmd_info *cmd);

// clean.c
int		clean_arg(char *arg);
int		clean_args(t_cmd_info *cmd);
void	reset_io(t_cmd_info *cmd);
void	free_hd_list(t_list **hds);

#endif
