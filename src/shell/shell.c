/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:42:12 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/27 17:23:31 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*extrude_workdir(char *path)
{
	int	len;

	len = ft_strlen(path) - 1;
	while (len >= 0 && path[len] != '/')
		len--;
	if (path[len] == '/')
		return (path + len + 1);
	else
		return (NULL);
}

int	set_prompt(char **prompt_addr, t_list **malloc_list)
{
	char	*path_abs;
	char	*tmp;
	char	*workdir_name;

	if (*prompt_addr)
		free(*prompt_addr);
	else
		add_to_malloc_list(malloc_list, *prompt_addr);
	path_abs = (char *)malloc(10000);
	path_abs = getcwd(path_abs, 10000);
	workdir_name = NULL;
	if (path_abs)
		workdir_name = extrude_workdir(path_abs);
	tmp = ft_strjoin(ROOT_PROMPT_PINK, workdir_name);
	*prompt_addr = ft_strjoin(tmp, "/ $ \x1b[0m");
	free(path_abs);
	free(tmp);
	return (0);
}

void	start_shell(t_app *app)
{
	char			*read_line;
	int				err;
	t_cmd_info		*cmd;
	t_parser_info	p_info;
	//TODO: create prompt
	while (1)
	{
		set_prompt(&app->prompt, &app->malloc_list);
		read_line = readline(app->prompt);
		//TODO: INIT P_INFO
		p_info.line = read_line;
		p_info.infile = 2;
		cmd = parser(p_info, &app->malloc_list);
		//TODO: What is the parsers error return?
		err = exe(app, cmd);
		if (err)
			exit_with_error(err);
		free_malloc_list(app);
		// cleanup
		free(read_line);
	}
}
