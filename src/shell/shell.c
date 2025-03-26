/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:42:12 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/25 16:03:10 by uschmidt         ###   ########.fr       */
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

int	set_prompt(char **prompt_addr)
{
	char	*path_abs;
	char	*tmp;
	char	*workdir_name;

	if (*prompt_addr)
		free(*prompt_addr);
	path_abs = (char *)malloc(10000);
	path_abs = getcwd(path_abs, 10000);
	workdir_name = NULL;
	if (path_abs)
		workdir_name = extrude_workdir(path_abs);
	tmp = ft_strjoin(ROOT_PROMPT_PINK, workdir_name);
	*prompt_addr = ft_strjoin(tmp, "/ $");
	free(path_abs);
	free(tmp);
	return (0);
}

void	start_shell(t_app *app)
{
	char	*read_line;
	//TODO: create prompt
	while (1)
	{
		set_prompt(&app->prompt);
		read_line = readline(app->prompt);
		// FORK -> EXE(PARSER(read_line)):
		// cleanup
		ft_printf("%s\n", read_line);
		free(read_line);
	}
}
