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

static int	replace_return(t_app *app, t_parser_info *p_info)
{
	char	*ret_val;
	char	*tmp;
	int		index[2];

	ret_val = ft_itoa(app->ret_val);
	if (ret_val == NULL)
		return (1);
	tmp = (char *)malloc_and_add_list(&app->malloc_list, sizeof(char)
		* (ft_strlen(p_info->line) + ft_strlen(ret_val) + -1));
	if (!tmp)
		return (1);
	index[0] = -1;
	index[1] = 0;
	while (p_info->line[++index[0]] && p_info->line[index[0]] != '$')
		tmp[index[0]] = p_info->line[index[0]];
	while (ret_val[index[1]])
		tmp[index[0]++] = ret_val[index[1]++];
	index[1] = index[0] - index[1] + 2;
	while (p_info->line[index[1]])
		tmp[index[0]++] = p_info->line[index[1]++];
	tmp[index[0]] = '\0';
	p_info->line = tmp;
	return (0);
}

//static int	replace_var(t_parser_info *p_info, char *p$)
//{
//}

int	expand(t_parser_info *p_info, t_app *app)
{
	char	*p$;

	p$ = ft_strchr(p_info->line, '$');
	while (p$ != NULL && *(p$ + 1) != '\0')
	{
		if (*(p$ + 1) == '?')
			replace_return(app, p_info);
	//	else
	//		replace_var(p_info, p$);
		ft_printf("LINE: %s\n", p_info->line);
		p$ = ft_strchr(p_info->line, '$');
	}
	return (0);
}
