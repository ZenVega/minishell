/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:50:01 by jhelbig           #+#    #+#             */
/*   Updated: 2025/04/30 12:23:27 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H
# define EXPORT_H

# include "../../error/error.h"
# include "../../includes/types.h"
# include "../../malloc_list/malloc_list.h"
# include "../../utils/utils.h"

int	ft_export(t_app *app, t_cmd_info *cmd);
int	export_with_args(t_app *app, t_cmd_info *cmd);

#endif
