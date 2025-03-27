/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_vars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:47:57 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/27 16:50:19 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printnbr(int fd, long long nbr)
{
	int		len;
	char	*num;

	len = 0;
	num = ft_itoa(nbr);
	len = ft_printstr(fd, num);
	free(num);
	return (len);
}

int	ft_printprcnt(int fd)
{
	write(fd, "%", 1);
	return (1);
}

static int	ft_ptr_len(unsigned long long ptr)
{
	int	len;

	len = 0;
	while (ptr != 0)
	{
		ptr /= 16;
		len++;
	}
	return (len);
}

int	ft_print_ptr(int fd, unsigned long long ptr)
{
	int	len;

	len = 0;
	len += write(fd, "0x", 2);
	if (ptr == 0)
		len += write(fd, "0", 1);
	else
	{
		ft_putull_base(ptr, "0123456789abcdef", 0, 16);
		len += ft_ptr_len(ptr);
	}
	return (len);
}
