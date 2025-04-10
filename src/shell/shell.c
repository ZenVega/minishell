/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:42:12 by uschmidt          #+#    #+#             */
/*   Updated: 2025/04/10 11:53:23 by jhelbig          ###   ########.fr       */
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
	//add_to_malloc_list(malloc_list, *prompt_addr);
	free(path_abs);
	free(tmp);
	return (0);
}


void	start_shell(t_app *app)
{
	char				*read_line;
	int					err;
	t_cmd_info			*cmd;
	t_parser_info		p_info;
	
	while (1)
	{
		init_sa_shell(app);	
	
		set_prompt(&app->prompt, &app->malloc_list);
		read_line = readline(app->prompt);
		if (read_line == NULL)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			free_malloc_list(app);
			free(app->prompt);
			free(read_line);
			break;
		}
		if (*read_line != '\0')
		{
			p_info = init_parser_info(0, 1, read_line);
			cmd = parser(p_info, &app->malloc_list, app);
			err = exe(app, cmd);
			add_history(read_line);
			free_malloc_list(app);
			free(read_line);
		}
	}
}
