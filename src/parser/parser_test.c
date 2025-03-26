/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:33:36 by jhelbig           #+#    #+#             */
/*   Updated: 2025/03/25 15:14:52 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "parser.h"
#include "../malloc_list/malloc_list.h"
#include "../libft/libft.h"

int main(int argc, char **argv)
{
	t_cmd_info	*cmd_info;
	t_list		*malloc_list;
	int			i;

	if (argc == 1)
	{
		ft_printf("please, give a string as an argument\n");
		return (1);
	}
	malloc_list = NULL;
	cmd_info = parser(argv[1], &malloc_list);
	ft_printf("infile fd: %d\n", cmd_info->infile);
	ft_printf("outfile fd: %d\n", cmd_info->outfile);
	ft_printf("cmd type: %d\n", cmd_info->type);
	
	i = 0;
	while (cmd_info->args && cmd_info->args[i])
	{
		ft_printf("cmd part %d: %s\n", i, cmd_info->args[i]);
		i++;
	}
	ft_lstclear(&malloc_list, free);	
}
