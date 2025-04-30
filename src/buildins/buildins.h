/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:15:49 by uschmidt          #+#    #+#             */
/*   Updated: 2025/04/28 10:44:47 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDINS_H
# define BUILDINS_H

# include <sys/wait.h>
# include "cd/cd.h"
# include "envp/env.h"
# include "envp/export.h"
# include "exit/exit.h"
# include "pwd/pwd.h"
# include "echo/echo.h"
# include "../includes/types.h"
# include "../signals/signals.h"

t_buildin	is_buildin(char *cmd);
int			exe_buildin(t_app *app, t_cmd_info *cmd);

#endif
