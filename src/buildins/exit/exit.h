/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:05:38 by jhelbig           #+#    #+#             */
/*   Updated: 2025/04/15 13:59:05 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H
# include "../../includes/types.h"
# include "../../exe/exe.h"
# include "../../error/error.h"
# include "../../malloc_list/malloc_list.h"

int		ft_exit(t_app *app, t_cmd_info *cmd);

#endif
