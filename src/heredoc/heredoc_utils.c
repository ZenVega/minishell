/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:31:57 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/21 16:01:48 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

static char	*get_hd_name(int count)
{
	char	*hd_name;
	char	*hd_id;

	hd_id = ft_itoa(count);
	if (!hd_id)
		return (NULL);
	hd_name = ft_strjoin("here_doc_", hd_id);
	if (!hd_name)
		return (free(hd_id), NULL);
	free(hd_id);
	return (hd_name);
}

char	*find_hd_name(int *fd)
{
	int		count;
	char	*hd_name;

	count = 0;
	*fd = -1;
	while (*fd < 0)
	{
		hd_name = get_hd_name(count);
		if (access(hd_name, F_OK))
			*fd = open(hd_name, O_RDWR | O_CREAT, 0777);
		else
			free(hd_name);
		count++;
	}
	return (hd_name);
}

static int	replace_str(t_parser_info *p_info, char *repl, char *pos, int len)
{
	char	*new_line;
	int		i;
	int		j;
	int		size;

	size = ft_strlen(p_info->line) - len + 2 + ft_strlen(repl);
	new_line = malloc(
			sizeof(char) * (size));
	if (new_line == NULL)
		return (1);
	i = -1;
	while (++i < (pos - p_info->line + 1))
		new_line[i] = p_info->line[i];
	j = 0;
	while (repl[j])
		new_line[i++] = repl[j++];
	while (pos[len])
		new_line[i++] = pos[len++];
	new_line[i] = '\0';
	p_info->line = new_line;
	return (0);
}

static char	*search_line(t_parser_info *p_info)
{
	char	*pos;

	pos = ft_strnstr(p_info->line, "<<", ft_strlen(p_info->line));
	while (pos)
	{
		if (p_info->mask[pos - p_info->line])
			pos = ft_strnstr(pos + 1, "<<", ft_strlen(pos + 1));
		else
			return (pos);
	}
	return (NULL);
}

int	rep_hd(t_app *app, t_parser_info *p_info, t_cmd_info *cmd, t_heredoc **hd)
{
	char		*pos;
	int			i;
	int			len;

	i = 2;
	pos = search_line(p_info);
	if (pos == NULL)
		return (1);
	*hd = (t_heredoc *)malloc(sizeof(t_heredoc));
	if (!hd)
		return (set_err(cmd, ERR_MALLOC, NULL), -1);
	if (pos[i] == '\0')
		return (set_err(cmd, ERR_SYNTAX, "after <<"), -1);
	while (ft_iswhitespace(pos[i]))
		i++;
	len = 0;
	while (!ft_iswhitespace(pos[i + len])
		&& pos[i + len] != '\0' && pos[i + len] != '|')
		len++;
	(*hd)->del = ft_substr(pos, i, len);
	(*hd)->doc_name = find_hd_name(&((*hd)->fd));
	if (replace_str(p_info, (*hd)->doc_name, pos, i + len))
		return (set_err(cmd, ERR_MALLOC, NULL), -1);
	add_to_malloc_list(&app->malloc_list, p_info->line);
	return (create_mask(p_info, &app->malloc_list, cmd));
}
