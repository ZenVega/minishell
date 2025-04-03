/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:42:12 by uschmidt          #+#    #+#             */
/*   Updated: 2025/04/03 11:08:28 by jhelbig          ###   ########.fr       */
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

//handling SIGINT to just display a newline
void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	start_shell(t_app *app)
{
	char				*read_line;
	int					err;
	t_cmd_info			*cmd;
	t_parser_info		p_info;
	struct sigaction	sa;

	sa.sa_handler = &handle_signal;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);

	while (1)
	{
		set_prompt(&app->prompt, &app->malloc_list);
		read_line = readline(app->prompt);
		// ctrl-D is EOF
		if (read_line == NULL)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			free_malloc_list(app);
			free(app->prompt);
			break;
		}
		if (*read_line != '\0')
		{
			p_info = init_parser_info(0, 1, read_line);
			cmd = parser(p_info, &app->malloc_list);
			err = exe(app, cmd);
			add_history(read_line);
			free_malloc_list(app);
			free(read_line);
		}
	}
}
