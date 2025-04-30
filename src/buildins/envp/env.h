/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:41:56 by jhelbig           #+#    #+#             */
/*   Updated: 2025/04/23 12:01:59 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include "../../includes/types.h"
# include "../../error/error.h"
# include "../../utils/utils.h"

int		env(t_app *app, t_cmd_info *cmd);
char	*get_env_val(t_app *app, char *key);

#endif
