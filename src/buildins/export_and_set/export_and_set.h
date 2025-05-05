/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_set.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:50:01 by jhelbig           #+#    #+#             */
/*   Updated: 2025/05/05 10:39:28 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_SET_H
# define EXPORT_SET_H

# include "../../error/error.h"
# include "../../includes/types.h"
# include "../../malloc_list/malloc_list.h"
# include "../../utils/utils.h"

//utils
int		found_var(char *var_line, char *cmd_line, int var_len);
int		update_var_arr(char *var_name, char *new_var, char **arr);
char	**add_var_to_array(char **array, char *new_var);
char	**rm_var_from_array(char **array, char *var);

//export_with_args
int		export_with_args(t_app *app, t_cmd_info *cmd);

//export
int		ft_export(t_app *app, t_cmd_info *cmd);

//set.c
int		set_var(t_app *app, t_cmd_info *cmd);
int		unset_var(t_app *app, t_cmd_info *cmd);

#endif
