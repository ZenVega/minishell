/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:08:48 by jhelbig           #+#    #+#             */
/*   Updated: 2025/05/02 11:40:19 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_H
# define SET_H

# include "export.h"
# include "../../error/error.h"
# include "../../includes/types.h"
# include "../../malloc_list/malloc_list.h" 
# include "../../utils/utils.h"

int set_var(t_app *app, t_cmd_info *cmd);

#endif
