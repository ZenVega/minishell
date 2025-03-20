/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:49:59 by jhelbig           #+#    #+#             */
/*   Updated: 2025/03/19 09:22:28 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//cmd_info_init.c
void	cmd_info_init(t_cmd_info *cmd_info);

//in_out.c
void	in_out(char **args, t_cmd_info *cmd, t_list **malloc_list);

void	set_infile(char **args, t_cmd_info *cmd, t_list **malloc_list);
void	set_outfile(char **args, t_cmd_info *cmd, t_list **malloc_list);


//parser_error.c
//void	free_args_split(char **args);
void	no_infile(char *file_name, t_list **malloc_list);
void	parse_error_near_nl(t_list **malloc_list);
