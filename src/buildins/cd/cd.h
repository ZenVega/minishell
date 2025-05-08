/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:43:13 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/02 15:12:30 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_H
# define CD_H

# include "../../includes/types.h"
# include "../env/env.h"
# include "../export_and_set/export_and_set.h"
# include "../../error/error.h"
# include "../../utils/utils.h"

int		cd(t_app *app, t_cmd_info *cmd);
//cd_utils
int		remove_last_route(char **path);
char	*get_home_path(t_app *app);

#endif
