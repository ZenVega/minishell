/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:49:59 by jhelbig           #+#    #+#             */
/*   Updated: 2025/04/01 15:55:20 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../includes/types.h"
# include "../libft/libft.h"
//parser.c
t_cmd_info	*parser(t_parser_info p_info, t_list **malloc_list);

//pipe_split.c
int			pipe_split(char **parts, char *line, t_list **malloc_list);

//cmd_info_init.c
t_cmd_info	*cmd_info_init(t_list **malloc_list, t_parser_info *p_info);

//in_out.c
int			set_io_files(char *line, t_cmd_info *cmd, t_list **malloc_list);
void		trim_args(char **args, t_cmd_info *cmd);

//infile.c
int			set_infile(char **args, t_cmd_info *cmd);
int			found_infile(char **args, int i, t_cmd_info *cmd);
int		simple_infile(char *file_name, t_cmd_info *cmd);

//outfile.c
int		set_outfile(char **args, t_cmd_info *cmd);
int		found_outfile(char **args, int i, t_cmd_info *cmd);
int		truncate_outfile(char *file_name, t_cmd_info *cmd);
int		append_outfile(char **args, int i, t_cmd_info *cmd);

//parser_error.c
//void	free_args_split(char **args);
void		no_infile(char *file_name, t_list **malloc_list);
void		parse_error_near_nl(t_list **malloc_list);
#endif
