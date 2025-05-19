/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:27:39 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/19 14:51:04 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	welcome_screen(char *envp[])
{
	int		pid;
	char	*args[3];

	args[0] = "cat";
	args[1] = "./welcome.txt";
	args[2] = NULL;
	pid = fork();
	if (pid == 0)
	{
		execve("/usr/bin/cat", args, envp);
		perror("execve failed");
		exit(-1);
	}
	else
		waitpid(pid, NULL, 0);
	return (0);
}
//line welcome_screen(envp); has to be commented out in order to pass the tests
int	main(int argc, char **argv, char *envp[])
{
	t_app				*app;

	if (argc != 1 || !argv)
	{
		write(2, "Invalid arguments\n", 18);
		return (-1);
	}
	//welcome_screen(envp);
	app = init_shell(envp);
	if (app == NULL)
		return (-1);
	start_shell(app);
	free_var_arr(app->envp);
	free(app);
	return (0);
}
