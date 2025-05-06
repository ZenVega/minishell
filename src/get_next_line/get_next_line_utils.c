/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 09:00:05 by jhelbig           #+#    #+#             */
/*   Updated: 2024/12/11 17:12:40 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	line_size(t_storebuffer **new_line_list)
{
	t_storebuffer	*temp;
	size_t			len;
	int				i;

	len = 0;
	temp = *new_line_list;
	while (temp)
	{
		i = 0;
		while (temp->content[i] != '\0' && temp->content[i] != '\n')
		{
			len++;
			i++;
		}
		if (temp->content[i] == '\n')
		{
			len++;
			return (len);
		}
		temp = temp->next;
	}
	return (len);
}

void	storebuffer_clear(t_storebuffer **lst)
{
	t_storebuffer	*temp;

	if (*lst == NULL)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

t_storebuffer	*find_last_node(t_storebuffer **new_line)
{
	t_storebuffer	*temp;

	temp = *new_line;
	if (temp == NULL)
		return (NULL);
	while (temp->next)
		temp = temp->next;
	return (temp);
}

// if list is empty, new is the start
// otherwise we find the last node and add new to the back
void	storebuffer_new_node_add_back(t_storebuffer **lst, char *content)
{
	t_storebuffer	*new;
	t_storebuffer	*temp;

	new = (t_storebuffer *)malloc(sizeof(t_storebuffer) * 1);
	if (!new)
		return ;
	new->content = content;
	new->next = NULL;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}
/*
void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	size_t	tlen;
	size_t	i;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	tlen = nmemb * size;
	if (tlen / size != nmemb)
		return (NULL);
	ptr = malloc(tlen);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < size)
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}*/
