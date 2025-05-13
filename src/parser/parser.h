/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:49:59 by jhelbig           #+#    #+#             */
/*   Updated: 2025/05/13 14:42:36 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>
# include "../error/error.h"
# include "../exe/exe.h"
# include "../includes/types.h"
# include "../libft/libft.h"
# include "../malloc_list/malloc_list.h"
# include "../utils/utils.h"
# include <readline/readline.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

//parser.c
t_cmd_info	*parser(t_parser_info p_info, t_app *app);

//pipe_split.c
int			pipe_split(char **parts, t_parser_info *p_info,
				t_list **malloc_list);

//cmd_info_init.c
t_cmd_info	*cmd_info_init(t_list **malloc_list, t_parser_info *p_info);

//expand.c
int			expand(t_parser_info *p_info, t_app *app, t_cmd_info *cmd);

//in_out.c
int			set_io_files(char *line, t_cmd_info *cmd, t_list **malloc_list,
				int *mask);
void		trim_args(char **args, t_cmd_info *cmd);

//in_out_utils.c
char		*clean_filename(char *filename);

//infile.c
int			set_infile(char **args, t_cmd_info *cmd);
int			found_infile(char **args, int i, t_cmd_info *cmd);
int			simple_infile(char *file_name, t_cmd_info *cmd);
int			here_doc(char *delimiter, t_cmd_info *cmd);

//mask.c
int			create_mask(t_parser_info *p_info, t_list **malloc_list,
				t_cmd_info *cmd);

//outfile.c
int			set_outfile(char **args, t_cmd_info *cmd);
int			found_outfile(char **args, int i, t_cmd_info *cmd);
int			truncate_outfile(char *file_name, t_cmd_info *cmd);
int			append_outfile(char *file_name, t_cmd_info *cmd);

#endif
