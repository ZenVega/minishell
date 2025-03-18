/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:49:59 by jhelbig           #+#    #+#             */
/*   Updated: 2025/03/18 09:53:42 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	cmd_info_init(t_cmd_info *cmd_info);

void	in_out(char **args, t_cmd_info *cmd);

void	set_infile(char **args, t_cmd_info *cmd);
