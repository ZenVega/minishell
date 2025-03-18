/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:49:59 by jhelbig           #+#    #+#             */
/*   Updated: 2025/03/18 10:31:31 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//cmd_info_init.c
void	cmd_info_init(t_cmd_info *cmd_info);

//in_out.c
void	in_out(char **args, t_cmd_info *cmd);

void	set_infile(char **args, t_cmd_info *cmd);

//parser_error.c
void	free_args_split(char **args);
void	no_infile(char **args, char *file_name);
void	parse_error_near_nl(char **args);
