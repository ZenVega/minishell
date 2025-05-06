/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 08:59:44 by jhelbig           #+#    #+#             */
/*   Updated: 2024/12/17 13:48:40 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
//random buffer size!

//read buffer by buffer until newline is found and store in list
//definitely NULL-terminate the buffer
//free buffer just at EOF necessarry - others overwritten
//do not read any more if we already have a newline left in list
void	read_buffers(t_storebuffer **new_line_list, int fd)
{
	int				read_count;
	char			*buffer;

	while (find_newline(new_line_list) == false)
	{
		buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (buffer == NULL)
			return ;
		buffer[0] = '\0';
		read_count = read(fd, buffer, BUFFER_SIZE);
		if (read_count <= 0)
		{
			free(buffer);
			return ;
		}
		buffer[read_count] = '\0';
		storebuffer_new_node_add_back(new_line_list, buffer);
	}
	return ;
}

//newline char somewhere in the current buffer
bool	find_newline(t_storebuffer **new_line_list)
{
	t_storebuffer	*temp;
	int				i;

	if (!*new_line_list)
		return (false);
	temp = *new_line_list;
	while (temp)
	{
		i = 0;
		while (temp->content[i])
		{
			if (temp->content[i] == '\n')
				return (true);
			i++;
		}
		temp = temp->next;
	}
	return (false);
}

//create the string by reading through the list until a newline is found
char	*create_next_line(t_storebuffer **new_line_list)
{
	char			*next_line;
	int				i;
	int				j;
	t_storebuffer	*temp;

	temp = *new_line_list;
	next_line = (char *)malloc((line_size(new_line_list) + 1) * sizeof(char));
	if (!next_line)
		return (NULL);
	i = 0;
	while (temp)
	{
		j = 0;
		while (temp->content[j] && temp->content[j] != '\n')
			next_line[i++] = temp->content[j++];
		if (temp->content[j] == '\n')
		{
			next_line[i++] = '\n';
			break ;
		}
		temp = temp->next;
	}
	next_line[i] = '\0';
	return (next_line);
}

// safe leftover content behind newline
// clear list
// put leftover in new node and set this new node as new first node
void	prepare_storebuffer_next_round(t_storebuffer **new_line_list)
{
	char			*rest;
	t_storebuffer	*last_node;
	int				i;
	int				j;

	last_node = find_last_node(new_line_list);
	if (!last_node)
		return ;
	i = 0;
	while (last_node->content[i] != '\0' && last_node->content[i] != '\n')
		i++;
	if (last_node->content[i] == '\0' || last_node->content[i + 1] == '\0')
		return (storebuffer_clear(new_line_list));
	i++;
	rest = (char *)malloc(BUFFER_SIZE - i + 1);
	if (!rest)
		return ;
	j = 0;
	while (last_node->content[i] != '\0')
		rest[j++] = last_node->content[i++];
	rest[j] = '\0';
	storebuffer_clear(new_line_list);
	storebuffer_new_node_add_back(new_line_list, rest);
}

//check for invalid fd, too little buffer_size and errors on read
char	*get_next_line(int fd)
{
	char					*next_line;
	static t_storebuffer	*new_line_list;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
	{
		storebuffer_clear(&new_line_list);
		return (NULL);
	}
	read_buffers(&new_line_list, fd);
	if (new_line_list == NULL || !new_line_list->content)
		return (NULL);
	next_line = create_next_line(&new_line_list);
	if (next_line[0] == '\0')
	{
		free(next_line);
		return (NULL);
	}
	prepare_storebuffer_next_round(&new_line_list);
	return (next_line);
}
/*
int	main(int argc, char **argv)
{
	int	fd;
	if (argc < 2 || argc > 2)
	{
		printf("too little or too many files given\n");
		return (-1);
	}
	fd = open(argv[1], O_RDONLY);
	int i;
	i = 0;
	while (i < 10)
	{
		char *next = get_next_line(fd);
		if(next == NULL)
			printf("NULL\n");
		else
			printf("%s", next);
		//printf("-");
		free(next);
		i++;
	}
	close(fd);
	return (0);
}*/
