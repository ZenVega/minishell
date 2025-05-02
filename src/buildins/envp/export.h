/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:50:01 by jhelbig           #+#    #+#             */
/*   Updated: 2025/05/02 11:31:37 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H
# define EXPORT_H

# include "../../error/error.h"
# include "../../includes/types.h"
# include "../../malloc_list/malloc_list.h"
# include "../../utils/utils.h"

char	**add_var_to_envp(char **envp, char *new_var);
int	update_var(char *var_name, char *new_var, t_app *app);
int	ft_export(t_app *app, t_cmd_info *cmd);
int	export_with_args(t_app *app, t_cmd_info *cmd);

#endif
