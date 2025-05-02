/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:07:52 by jhelbig           #+#    #+#             */
/*   Updated: 2025/05/02 14:29:20 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "set.h"

int set_var(t_app *app, t_cmd_info *cmd)
{
	char	*addr_equal;
	char	*var_name;
	int		i;
	t_list	*new_local;
	
	i = 0;
	while (cmd->args[i])
	{
		addr_equal = ft_strchr(cmd->args[i], '=');
		var_name = ft_substr(cmd->args[i], 0, (size_t)(addr_equal - cmd->args[i]));
		//fall: var already in envp --> update in envp
		if (update_var(var_name, cmd->args[i], app) == 1)
		{// if not: set var in local list
			new_local = ft_lstnew(ft_strdup(cmd->args[i]));
			ft_lstadd_back(app->local_var, new_local);		
		}	
		free(var_name);
		i++;
	}
	return (0);
	
}
