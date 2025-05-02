/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:07:52 by jhelbig           #+#    #+#             */
/*   Updated: 2025/05/02 11:53:11 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "set.h"

int set_var(t_app *app, t_cmd_info *cmd)
{
	char	*addr_equal;
	char	*var_name;
	
	addr_equal = ft_strchr(cmd->args[0], '=');
	var_name = ft_substr(cmd->args[0], 0, (size_t)(addr_equal - cmd->args[0]));
	//fall: var already in envp --> update in envp
	if (update_var(var_name, cmd->args[0], app) == 1)
		return (1);
			//then set in local list
	
	// var not yet in envp
	//free(var_name);
	return (0);
}
