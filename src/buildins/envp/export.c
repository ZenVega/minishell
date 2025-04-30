/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:49:45 by jhelbig           #+#    #+#             */
/*   Updated: 2025/04/30 10:02:31 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

int	export_no_args(t_app *app)
{
	char	**print;
	int		i;
	char	*addr_equal;
	char	*substr;

	print = copy_and_qsort(app->envp);
	if (!print)
		return (-1);
	i = 0;
	while (print[i])
	{
		addr_equal = ft_strchr(print[i], '=');
		//print until and including = then "var_val"
		if (addr_equal != NULL)
		{	
			substr = ft_substr(print[i], 0, (size_t)(addr_equal - print[i] + 1));
			ft_printf("declare -x %s\"%s\"\n", substr, addr_equal + 1);
			free(substr);
		}
		else
			ft_printf("declare -x %s\n", print[i]);
		i++;
	}
	free_envp(print);
	app->ret_val = 0;
	return (0);
}

int	invalid_identifier(char *arg)
{
	int		c;
	char	*addr_equal;
	char	*addr_char;

	addr_equal = ft_strchr(arg, '=');
	c = 33;	
	while (c <= 128)
	{
		addr_char = ft_strchr(arg, (char)c);
		if(addr_char != NULL && addr_char < addr_equal)
			return (1);
		if (c == 47)
			c = 57;
		else if (c == 64)
			c = 90;
		else if (c == 96)
			c = 122;
		c++;	
	}
	return (0);
}

int	export_with_args(t_app *app, t_cmd_info *cmd)
{
	int	i;
	int err;
	
	err = 0;
	i = 1;
	while (cmd->args[i])
	{
		//if var name invalid
		// just before the =
		if (ft_isdigit(cmd->args[i][0]) == 1
			|| cmd->args[i][0] == '='
			|| invalid_identifier(cmd->args[i]) == 1) 

		{
			ft_fprintf(2, "minishell: export: '%s': not a valid identifier", cmd->args[1]);
			app->ret_val = 1;
		}
		//if var="val"
	//	if (ft_strchr(cmd->args[i], '=') != NULL)
	//		err = set_var_with_val(app, cmd);
		//if var

		i++;
	}
	return (err);
}

int	ft_export(t_app *app, t_cmd_info *cmd)
{
	if (!cmd->args[1])
		return (export_no_args(app));
	else
		return (export_with_args(app, cmd));
	return (0);
}
