/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:00:35 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/17 11:51:48 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

void	isolate_cmd(char *args, char *dest)
{
	size_t	i;

	i = 0;
	while (is_space(*args))
		args++;
	while (!is_space(args[i]))
		i++;
	//TODO: add track_malloc
	dest = (char *)malloc(sizeof(char) * i);
	ft_strlcpy(dest, args, i);
}

//  all possible checks
//  cmd_info has all necessary keys set
//  argv[0] has no special characters
//  ...
int	is_valid(t_cmd_info *cmd)
{
	if (cmd->type != 0)
		return (1);
	return (0);
}
