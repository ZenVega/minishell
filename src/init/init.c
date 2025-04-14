/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:03:56 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/25 15:52:47 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

int	mask_substr(char *line, int pos, int *mask, char c)
{
	char	*tmp;
	int		mask_id;

	mask_id = 1;
	if (c == '"')
		mask_id = 2;
	tmp = ft_strchr(((&line[pos]) + 1), c);
	if (tmp == NULL)
	{
		mask[pos] = 0;
		return (pos + 1);
	}
	else
		while (line + pos <= tmp)
			mask[pos++] = mask_id;
	return (pos);
}

int	create_mask(t_parser_info p_info, t_list **malloc_list, t_cmd_info *cmd)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(p_info.line);
	p_info.mask = (int *)malloc_and_add_list(malloc_list, sizeof(int) * len);
	if (!p_info.mask)
		return (set_err(cmd, ERR_MALLOC, NULL));
	while (p_info.line[i])
	{
		while (p_info.line[i]
			&& p_info.line[i] != '"' && p_info.line[i] != '\'')
			p_info.mask[i++] = 0;
		if (p_info.line[i] == '"' || p_info.line[i] == '\'')
			i = mask_substr(p_info.line, i, p_info.mask, p_info.line[i]);
	}
	ft_printf("MASK: ", p_info.mask[i]);
	for (int i = 0; i < len; i++)
		ft_printf("%d", p_info.mask[i]);
	ft_printf("\n", p_info.mask[i]);
	return (0);
}

t_parser_info	init_parser_info(int infile, int outfile, char *line)
{
	t_parser_info	p_info;

	p_info.infile = infile;
	p_info.outfile = outfile;
	p_info.line = line;
	p_info.mask = NULL;
	return (p_info);
}

t_app	*init_shell(char *envp[])
{
	t_app	*app;

	app = (t_app *)malloc(sizeof(t_app));
	if (!app)
		return (NULL);
	app->malloc_list = NULL;
	app->envp = envp;
	app->prompt = NULL;
	return (app);
}
