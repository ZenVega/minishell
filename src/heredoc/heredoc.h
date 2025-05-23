/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:42:00 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/23 12:13:24 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include <fcntl.h>
# include "../error/error.h"
# include "../expand/expand.h"
# include "../includes/types.h"
# include "../libft/libft.h"
# include "../malloc_list/malloc_list.h"
# include "../mask/mask.h"
# include "../signals/signals.h"

# include <readline/readline.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

//heredoc.c
int			create_heredoc(t_app *app, t_parser_info *p_info, t_cmd_info *cmd);
int			here_doc(t_app *app, char *delimiter, t_cmd_info *cmd);

//heredoc_utils.c
char		*find_hd_name(int *fd);
int			rep_hd(t_app *app, t_parser_info *p_info, t_cmd_info *cmd, t_heredoc **hd);

//heredoc_signals.c
void		init_signal_hd_parent(t_app *app);
void		init_signal_hd_child(t_app *app);
#endif
