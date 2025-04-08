/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:17:52 by uschmidt          #+#    #+#             */
/*   Updated: 2025/04/08 15:24:54 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PWD_H
# define PWD_H
# include "../../includes/types.h"
# include "../../error/error.h"

int		pwd(t_app *app, t_cmd_info *cmd);
char	*get_cwd(void);

#endif
