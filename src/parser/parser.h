/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:49:59 by jhelbig           #+#    #+#             */
/*   Updated: 2025/03/25 13:55:10 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//parser.c
t_cmd_info	*parser(char *line, t_list **malloc_list);

//pipe_split.c
char **pipe_split(char *line, t_list **malloc_list);

//cmd_info_init.c
t_cmd_info	*cmd_info_init(t_list **malloc_list);

//in_out.c
void	set_io_files(char *line, t_cmd_info *cmd, t_list **malloc_list);
void    trim_args(char **args, t_cmd_info *cmd);

//infile.c
void	set_infile(char **args, t_cmd_info *cmd, t_list **malloc_list);
void    found_infile(char **args, int i, t_cmd_info *cmd, t_list **malloc_list);
void    simple_infile(char *file_name, t_cmd_info *cmd, t_list **malloc_list);

//outfile.c
void	set_outfile(char **args, t_cmd_info *cmd, t_list **malloc_list);
void    found_outfile(char **args, int i, t_cmd_info *cmd, t_list **malloc_list);
void    truncate_outfile(char *file_name, t_cmd_info *cmd, t_list **malloc_list);
void    append_outfile(char **args, int i, t_cmd_info *cmd, t_list **malloc_list);


//parser_error.c
//void	free_args_split(char **args);
void	no_infile(char *file_name, t_list **malloc_list);
void	parse_error_near_nl(t_list **malloc_list);
