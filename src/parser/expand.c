/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:02:45 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/05 14:58:40 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
static int	expand_var(t_app *app, t_parser_info *p_info, char *var, int var_len)
{
	int		len_newline;
	int		i;
	int		j;
	int		k;
	char	*ret_val;

	i = -1;
	j = -1;
	len_newline = ft_strlen(p_info->line) - var_len;
	len_newline += ft_strlen(var) - var_len - 1;
	ret_val = (char *)malloc_and_add_list(&app->malloc_list, sizeof(char)
		* len_newline + 1);
	if (!ret_val)
		return (1);
	while (p_info->line[++i] && p_info->line[i] != '$')
		ret_val[i] = p_info->line[i];
	k = i;
	var += var_len + 1;
	while (var[++j])
		ret_val[i++] = var[j];
	while (i < len_newline)
		ret_val[i++] = p_info->line[k++];
	p_info->line = ret_val;
	return (0);
}

static int	replace_return(t_app *app, t_parser_info *p_info)
{
	char	*ret_val;

	ret_val = ft_itoa(app->ret_val);
	return (expand_var(app, p_info, ret_val, ft_strlen(ret_val)));
	//if (ret_val == NULL)
	//	return (1);
	//tmp = (char *)malloc_and_add_list(&app->malloc_list, sizeof(char)
	//	* (ft_strlen(p_info->line) + ft_strlen(ret_val) + -1));
	//if (!tmp)
	//	return (1);
	//index[0] = -1;
	//index[1] = 0;
	//while (p_info->line[++index[0]] && p_info->line[index[0]] != '$')
	//	tmp[index[0]] = p_info->line[index[0]];
	//while (ret_val[index[1]])
	//	tmp[index[0]++] = ret_val[index[1]++];
	//index[1] = index[0] - index[1] + 2;
	//while (p_info->line[index[1]])
	//	tmp[index[0]++] = p_info->line[index[1]++];
	//tmp[index[0]] = '\0';
	//p_info->line = tmp;
	return (0);
}

static int	replace_var(t_app *app, t_parser_info *p_info, char *p$)
{
	int	var_len;
	int	i;

	i = -1;
	var_len = ft_strlen(p$);
	while (--var_len > 0)
	{
		while (app->envp[++i])
			if (!ft_strncmp(p$ + 1, app->envp[i], var_len))
				return (expand_var(app, p_info, app->envp[i], var_len)); 
		i = -1;
		while (app->local_var[++i])
			if (!ft_strncmp(p$ + 1, app->local_var[i], var_len))
				return (expand_var(app, p_info, app->local_var[i], var_len)); 
	}
	return (expand_var(app, p_info, "", var_len));
}

int	expand(t_parser_info *p_info, t_app *app)
{
	char	*p$;

	p$ = ft_strchr(p_info->line, '$');
	while (p$ != NULL && *(p$ + 1) != '\0')
	{
		if (*(p$ + 1) == '?')
			replace_return(app, p_info);
		else
			replace_var(app, p_info, p$);
		p$ = ft_strchr(p_info->line, '$');
	}
	ft_printf("LINE: %s\n", p_info->line);
	return (0);
}
