/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:24:14 by uschmidt          #+#    #+#             */
/*   Updated: 2025/04/28 10:47:33 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h" 

int	is_space(char c)
{
	if (
		c == ' '
		|| c == '\b'
		|| c == '\t'
		|| c == '\n'
		|| c == '\v'
	) 
		return (1);
	return (0);
}

char	**copy_envp(char **envp)
{
	int		size;
	int		i;
	char	**copy;

	size = 0;
	while (envp[size])
		size++;
	copy = (char **)malloc(sizeof(char *) * (size + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i]) 
		{
			free_var_arr(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int	get_char_arr_len(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		i++;
	return (i);
}

void	reroute_io(int input, int output)
{
	if (input != STDIN_FILENO)
		dup2(input, STDIN_FILENO);
	if (output != STDOUT_FILENO)
		dup2(output, STDOUT_FILENO);
}

int	has_access_ret(t_app *app, t_cmd_info *cmd, char *path)
{
	struct stat	sb;

	stat(path, &sb);
	if ((sb.st_mode & S_IFMT) == S_IFDIR)
		return (app->ret_val = 126, set_err(cmd, ERR_IS_FOLDER, path));
	else if (access(path, F_OK))
		return (app->ret_val = 127, set_err(cmd, ERR_NO_FILE, path));
	else if (access(path, X_OK))
		return (app->ret_val = 126, set_err(cmd, ERR_PERM, path));
	return (0);
}
