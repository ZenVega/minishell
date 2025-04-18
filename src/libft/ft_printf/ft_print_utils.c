/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:57:28 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/27 17:14:05 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printchar(int fd, char c)
{
	ft_putchar_fd(c, fd);
	return (1);
}

int	ft_printstr(int fd, char *str)
{
	int	len;

	if (!str)
	{
		ft_putstr_fd("(null)", fd);
		return (6);
	}
	len = ft_strlen(str);
	ft_putstr_fd(str, fd);
	return (len);
}

int	ft_printptr(int fd, void *ptr)
{
	int					len;
	unsigned long long	temp;

	len = 2;
	temp = (unsigned long long)ptr;
	if (ptr == NULL)
	{
		ft_putstr_fd("(nil)", fd);
		return (5);
	}
	ft_putstr_fd("0x", fd);
	while (temp)
	{
		temp /= 16;
		len++;
	}
	ft_putull_base_fd(fd, (unsigned long long)ptr, "0123456789abcdef", 0);
	return (len);
}
