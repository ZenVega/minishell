/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:05:38 by jhelbig           #+#    #+#             */
/*   Updated: 2025/04/28 10:48:22 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H
# include "../../error/error.h"
# include "../../includes/types.h"
# include "../../libft/libft.h"
# include "../../malloc_list/malloc_list.h"
# include "../../utils/utils.h"

int		ft_exit(t_app *app, t_cmd_info *cmd);

#endif
