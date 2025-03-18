/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:33:36 by jhelbig           #+#    #+#             */
/*   Updated: 2025/03/18 10:00:43 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "parser.h"

int main(int argc, char **argv)
{
	char 		**split;
	t_cmd_info	cmd_info;
	if (argc == 1)
	{
		ft_printf("please, give a string as an argument\n");
		return (1);
	}
	split = ft_split(argv[1], ' ');
	cmd_info_init(&cmd_info);
	in_out(split, &cmd_info);
	ft_printf("infile fd: %d\n", cmd_info.infile);	
}
