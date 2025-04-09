/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:15:49 by uschmidt          #+#    #+#             */
/*   Updated: 2025/04/08 14:56:48 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDINS_H
# define BUILDINS_H

# include <sys/wait.h>
# include "pwd/pwd.h"
# include "../includes/types.h"

t_buildin	is_buildin(char *cmd);
int			exe_buildin(t_app *app, t_cmd_info *cmd);
#endif
