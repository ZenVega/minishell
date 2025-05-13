/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:58:47 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/13 11:47:27 by jhelbig          ###   ########.fr       */
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

	if (cmd == NULL)
		return (-1);
	err = cmd->err_info.code;
	if (err)
		return (exit_with_error(*cmd));
	if (cmd->type == BIN)
		err = exe_bin(app, cmd);
	else if (cmd->type == PIPE)
		err = open_pipe(app, cmd);
	if (err)
		return (exit_with_error(*cmd));
	return (err);
}
