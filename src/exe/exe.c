/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:58:47 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/19 11:24:39 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

// exe takes the cmd struct
// checks if the input is valid
// and executes the corresponding function
// if there is an err, we exit cleanly
int	exe(t_app *app, t_cmd_info *cmd)
{
	int	err;

	err = is_valid(cmd);
	if (err)
		return (err);
//		on_error();
	if (cmd->type == BIN)
	{
		err = exe_bin(app, cmd);
		return (err);
	}
	//TODO: CLEANUP 
	return (err);
}
