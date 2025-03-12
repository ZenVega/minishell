/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:58:47 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/12 16:25:12 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

// exe takes the cmd struct
// checks if the input is valid
// and executes the corresponding function
// if there is an err, we exit cleanly
// int execv(const char *pathname, char *const argv[]);
int	exe(t_cmd_info *cmd)
{
	if (!is_valid(cmd))
		return (1);
//		on_error();
	if (cmd->type == BIN)
		return (exe_bin(cmd));
	return (1);
}
