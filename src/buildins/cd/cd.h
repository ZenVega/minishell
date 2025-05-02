/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:43:13 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/02 11:31:36 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_H
# define CD_H

# include "../../includes/types.h"
# include "../envp/env.h"
# include "../../error/error.h"
# include "../../utils/utils.h"

int	cd(t_app *app, t_cmd_info *cmd);

#endif
