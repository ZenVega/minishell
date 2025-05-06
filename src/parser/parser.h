/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:49:59 by jhelbig           #+#    #+#             */
/*   Updated: 2025/05/06 10:57:16 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>
# include "../error/error.h"
# include "../get_next_line/get_next_line.h"
# include "../includes/types.h"
# include "../libft/libft.h"
# include "../malloc_list/malloc_list.h"

//parser.c
t_cmd_info	*parser(t_parser_info p_info, t_list **malloc_list);

//pipe_split.c
int			pipe_split(char **parts, t_parser_info *p_info, t_list **malloc_list);

//cmd_info_init.c
t_cmd_info	*cmd_info_init(t_list **malloc_list, t_parser_info *p_info);

//in_out.c
int			set_io_files(char *line, t_cmd_info *cmd, t_list **malloc_list, int *mask);
void		trim_args(char **args, t_cmd_info *cmd);

//infile.c
int			set_infile(char **args, t_cmd_info *cmd);
int			found_infile(char **args, int i, t_cmd_info *cmd);
int			simple_infile(char *file_name, t_cmd_info *cmd);
int         here_doc(char *delimiter, t_cmd_info *cmd);

//mask.c
int			create_mask(t_parser_info *p_info, t_list **malloc_list, t_cmd_info *cmd);

//outfile.c
int			set_outfile(char **args, t_cmd_info *cmd);
int			found_outfile(char **args, int i, t_cmd_info *cmd);
int			truncate_outfile(char *file_name, t_cmd_info *cmd);
int			append_outfile(char *file_name, t_cmd_info *cmd);

#endif
