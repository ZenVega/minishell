/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:02:45 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/05 12:05:43 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	replace_return(int ret_int, t_parser_info *p_info, char *p$)
{
	char	*ret_str;
	char	*tmp;
	int		len_line;
	int		len_ret;
	int		index[2];

	len_line = ft_strlen(p_info->line);
	ret_str = ft_itoa(ret_int);
	if (ret_str == NULL)
		return (1);
	len_ret = ft_strlen(ret_str);
	tmp = (char *)malloc(sizeof(char) * (len_line + len_ret + -1));
	if (!tmp)
		return (1);
	index[0] = 0;
	index[1] = 0;
	while (p_info->line[index[0]] && p_info->line[index[0]] != '$')
		tmp[index[0]] = p_info->line[index[0]++];
	while (ret_str[index[1]])
		tmp[index[0]++] = ret_str[index[1]++];
	index[1] = index[0] - index[1] + 2;
	while (p_info->line[index[1]])
		tmp[index[0]++] = p_info->line[index[1]++];
	free(p_info->line);
	p_info->line = tmp;
	return (0);
}

static int	replace_var(t_parser_info *p_info, char *p$)
{
}

int	expand(t_parser_info *p_info, t_app *app)
{
	char	*p$;

	p$ = ft_strchr(p_info->line, '$');
	if (p$ == NULL || *(p$ + 1) == '\0')
		return (0);
	if (*(p$ + 1) == '0')
		replace_return(app->ret_val, p_info, p$);
	else
		replace_var(p_info, p$);
	return (0);
}
