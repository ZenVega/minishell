/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_and_set_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 09:10:18 by jhelbig           #+#    #+#             */
/*   Updated: 2025/05/14 13:28:59 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export_and_set.h"

int	found_var(char *var_line, char *cmd_line, int var_len)
{
	if (ft_strncmp(var_line, cmd_line, var_len) == 0
		&& (var_line[var_len] == '=' || var_line[var_len] == '\0'))
		return (1);
	return (0);
}

int	update_var_arr(char *var_name, char *new_var, char **arr)
{
	int	i;
	int	var_len;

	i = 0;
	var_len = ft_strlen(var_name);
	while (arr && arr[i])
	{
		if (ft_strncmp(arr[i], var_name, var_len) == 0
			&& (arr[i][var_len] == '=' || arr[i][var_len] == '\0'))
		{
			free(arr[i]);
			arr[i] = ft_strdup(new_var);
			return (0);
		}
		i++;
	}
	return (1);
}

char	**add_var_to_array(char **array, char *new_var)
{
	int		size;
	int		i;
	char	**new;

	size = 0;
	i = 0;
	while (array && array[size])
		size++;
	new = (char **)malloc(sizeof(char *) * (size + 2));
	if (!new)
		return (NULL);
	while (i < size)
	{
		new[i] = ft_strdup(array[i]);
		if (!new[i])
			return (free_var_arr(new), NULL);
		i++;
	}
	new[i++] = ft_strdup(new_var);
	if (!new[i - 1])
		return (NULL);
	new[i] = NULL;
	free_var_arr(array);
	return (new);
}

char	**rm_var_from_array(char **array, char *var)
{
	int		i;
	int		j;
	int		size;
	int		var_len;
	char	**new;

	size = get_char_arr_len(array);
	new = (char **)malloc(sizeof(char *) * size);
	if (!new)
		return (NULL);
	var_len = ft_strlen(var);
	i = 0;
	j = 0;
	while (array[i])
	{
		if (found_var(array[i], var, var_len))
			i++;
		else
		{
			new[j++] = ft_strdup(array[i++]);
			if (!new[j - 1])
				return (free_var_arr(new), NULL);
		}
	}
	return (new[j] = NULL, new);
}
