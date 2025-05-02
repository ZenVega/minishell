/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:07:52 by jhelbig           #+#    #+#             */
/*   Updated: 2025/05/02 15:38:17 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export_set.h"

int	update_local_var(char *var_name, char *new_var, t_app *app)
{
	t_list	*local;
	int		var_len;

	local = *app->local_var;
	var_len = ft_strlen(var_name);
	while (local)
	{
		if (ft_strncmp(local->content, var_name, var_len) == 0
			&& (((char *)local->content)[var_len] == '=' 
			|| ((char *)local->content)[var_len] == '\0'))
		{
			free(local->content);
			local->content = ft_strdup(new_var);
			return (0);
		}
		local = local->next;
	}
	return (1);
}

int	set_var(t_app *app, t_cmd_info *cmd)
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
		if (update_env_var(var_name, cmd->args[i], app) == 1)
		{
			if (update_local_var(var_name, cmd->args[i], app) == 1)
			{
				new_local = ft_lstnew(ft_strdup(cmd->args[i]));
				ft_lstadd_back(app->local_var, new_local);
			}
		}
		free(var_name);
		i++;
	}
	return (0);
}

char	**rm_var_from_envp(char **envp, char *var)
{
	int		size;
	int		i;
	char	**new;

	size = 0;
	while (envp[size])
		size++;
	new = (char **)malloc(sizeof(char *) * size);
	if (!new)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0)
			i++;
		else
		{
			new[i] = ft_strdup(envp[i]);
			if (!new[i]) 
				return (free_envp(new), NULL);
			i++;
		}
	}
	new[i] = NULL;
	return (free_envp(envp), new);
}

int	unset_var(t_app *app, t_cmd_info *cmd)
{
	int	i;
	int	j;
	int	var_len;

	j = 1;
	while (cmd->args[j])
	{
		i = 0;
		while (app->envp[i])
		{
			var_len = ft_strlen(cmd->args[j]);
			if (ft_strncmp(app->envp[i], cmd->args[j], var_len) == 0
				&& (app->envp[i][var_len] == '=' 
				|| app->envp[i][var_len] == '\0'))
			{
				app->envp = rm_var_from_envp(app->envp, cmd->args[j]);
				return (0);
			}
			i++;
		}
		j++;
	}
	return (0);
}
