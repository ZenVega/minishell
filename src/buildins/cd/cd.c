/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:40:05 by uschmidt          #+#    #+#             */
/*   Updated: 2025/04/28 11:52:02 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

static char	*get_abs_path(char *path)
{
	return (path);
}

// set OLDPWD as current PWD
// get 'directory value'
// expand args / clean string
// set PWD
// updateprompt if necessary
int	cd(t_app *app, t_cmd_info *cmd)
{
	char	*abs_path;

	if (!app)
		return (-1);
	if (get_char_arr_len(cmd->args) != 2)
		return (set_err(cmd, ERR_NUM_ARGS, "CD"));
	abs_path = get_abs_path(cmd->args[1]);
	chdir(abs_path);
	return (0);
}
