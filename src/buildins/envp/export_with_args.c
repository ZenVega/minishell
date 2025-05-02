/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_with_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:19:13 by jhelbig           #+#    #+#             */
/*   Updated: 2025/05/02 15:35:41 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export_set.h"

int	invalid_identifier(char *arg)
{
	int		c;
	char	*addr_equal;
	int		len;
	int		i;

	addr_equal = ft_strchr(arg, '=');
	if (!addr_equal)
		len = ft_strlen(arg);
	else
		len = addr_equal - arg;
	i = 0;
	while (i < len)
	{
		c = arg[i];
		if (!(ft_isdigit(c) || ft_isalpha(c) || c == '_'))
			return (1);
		i++;
	}
	return (0);
}

char	**add_var_to_envp(char **envp, char *new_var)
{
	int		size;
	int		i;
	char	**new;

	size = 0;
	while (envp[size])
		size++;
	new = (char **)malloc(sizeof(char *) * (size + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new[i] = ft_strdup(envp[i]);
		if (!new[i]) 
		{
			free_envp(new);
			return (NULL);
		}
		i++;
	}
	new[i++] = ft_strdup(new_var);
	new[i] = NULL;
	free_envp(envp);
	return (new);
}

int	copy_from_loc_to_envp(char *var_name, t_app *app)
{
	t_list	*local;
	int		var_len;

	var_len = ft_strlen(var_name);
	local = *(app->local_var);
	while (local)
	{
		if (ft_strncmp(local->content, var_name, var_len) == 0
			&& (((char *)(local->content))[var_len] == '=' 
			|| ((char*)local->content)[var_len] == '\0'))
		{
			app->envp = add_var_to_envp(app->envp, local->content);
			return (0);
		}
		local = local->next;
	}
	return (1);
}

int	update_env_var(char *var_name, char *new_var, t_app *app)
{
	int		i;
	int		var_len;

	i = 0;
	var_len = ft_strlen(var_name);
	while (app->envp[i])
	{
		if (ft_strncmp(app->envp[i], var_name, var_len) == 0
			&& (app->envp[i][var_len] == '=' 
			|| app->envp[i][var_len] == '\0'))
		{
			free(app->envp[i]);
			app->envp[i] = ft_strdup(new_var);
			update_local_var(var_name, new_var, app);
			return (0);
		}
		i++;
	}
	return (1);
}

int	update_or_add_var(char *var_name, char *var_val, t_app *app)
{
	char	*tmp;
	char	*new_var;

	if (var_val != NULL)
	{
		tmp = ft_strjoin(var_name, "=");
		new_var = ft_strjoin(tmp, var_val);
		free(tmp);
	}
	else
		new_var = ft_strdup(var_name);
	if (update_env_var(var_name, new_var, app) == 1)
		app->envp = add_var_to_envp(app->envp, new_var);
	if (var_val != NULL)
		free(var_name);
	free(new_var);
	return (0);
}

int	set_export_var(t_app *app, char *arg)
{
	char	*var_name;
	char	*addr_equal;

	addr_equal = ft_strchr(arg, '=');
	if (addr_equal != NULL)
	{
		var_name = ft_substr(arg, 0, (size_t)(addr_equal - arg));
		return (update_or_add_var(var_name, addr_equal + 1, app));
	}
	else
	{
		var_name = arg;
		if (copy_from_loc_to_envp(var_name, app) == 1)
			return (update_or_add_var(var_name, NULL, app));
		return (0);
	}
}

int	export_with_args(t_app *app, t_cmd_info *cmd)
{
	int	i;
	int	err;

	err = 0;
	i = 1;
	while (cmd->args[i])
	{
		if (ft_isdigit(cmd->args[i][0]) == 1
			|| cmd->args[i][0] == '='
			|| invalid_identifier(cmd->args[i]) == 1)
		{
			ft_fprintf(2, "minishell: export: '%s': not a valid identifier\n",
				cmd->args[i]);
			app->ret_val = 1;
		}
		else
		{
			err = set_export_var(app, cmd->args[i]);
		}
		i++;
	}
	return (err);
}
