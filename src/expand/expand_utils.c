/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:48:12 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/19 14:42:06 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static int	remove_var(t_parser_info *p_info)
{
	int	i;
	int	j;

	i = 0;
	while (p_info->line[i] && p_info->line[i] != '$')
		i++;
	j = i++;
	while (p_info->line[i] && !is_space(p_info->line[i])
		&& p_info->line[i] != '$' && p_info->line[i] != '='
		&& p_info->line[i] != '"' && p_info->line[i] != '\'')
		i++;
	while (p_info->line[i])
		p_info->line[j++] = p_info->line[i++];
	while (p_info->line[j])
		p_info->line[j++] = 0;
	return (0);
}

static int	expand_var(t_app *app, t_parser_info *p_info, 
		char *var, int var_len)
{
	int		len_newline;
	int		i;
	int		j;
	int		k;
	char	*ret_val;

	i = -1;
	j = -1;
	len_newline = ft_strlen(p_info->line) - (2 * var_len) + ft_strlen(var) - 1;
	ret_val = (char *)malloc_and_add_list(&app->malloc_list, sizeof(char)
			* len_newline + 1);
	if (!ret_val)
		return (-1);
	while (p_info->line[++i]
		&& (p_info->line[i] != '$' || p_info->mask[i] == 1))
		ret_val[i] = p_info->line[i];
	k = i + var_len + 1;
	var += var_len + 1;
	while (var[++j])
		ret_val[i++] = var[j];
	j = i;
	while (i < len_newline)
		ret_val[i++] = p_info->line[k++];
	p_info->line = ret_val;
	return (j);
}

int	replace_return(t_app *app, t_parser_info *p_info, int i_dol)
{
	char	*ret_val;
	char	*var;
	int		index[2];

	var = ft_itoa(app->ret_val);
	if (var == NULL)
		return (-1);
	ret_val = (char *)malloc_and_add_list(&app->malloc_list, sizeof(char)
			* (ft_strlen(p_info->line) + ft_strlen(var) - 1));
	if (!ret_val)
		return (-1);
	index[0] = -1;
	index[1] = 0;
	while (++index[0] < i_dol)
		ret_val[index[0]] = p_info->line[index[0]];
	while (var[index[1]])
		ret_val[index[0]++] = var[index[1]++];
	index[1] = index[0] - index[1] + 2;
	//free(var);
	while (p_info->line[index[1]])
		ret_val[index[0]++] = p_info->line[index[1]++];
	ret_val[index[0]] = '\0';
	p_info->line = ret_val;
	return (i_dol + ft_strlen(var) - 2);
}

int	replace_var(t_app *app, t_parser_info *p_info, char *p_dol)
{
	int	var_len;
	int	i;

	i = -1;
	var_len = 1;
	while (p_dol[var_len] && p_dol[var_len] != '$' && p_dol[var_len] != ' ')
		var_len++;
	while (--var_len > 0)
	{
		while (app->envp[++i])
			if (!ft_strncmp(p_dol + 1, app->envp[i], var_len)
				&& (app->envp[i][var_len] == '='
				|| app->envp[i][var_len] == '\0'))
				return (expand_var(app, p_info, app->envp[i], var_len)); 
		i = -1;
		while (app->local_var[++i])
			if (!ft_strncmp(p_dol + 1, app->local_var[i], var_len)
				&& (app->local_var[i][var_len] == '='
				|| app->local_var[i][var_len] == '\0'))
				return (expand_var(app, p_info, app->local_var[i], var_len)); 
	}
	return (remove_var(p_info));
}
