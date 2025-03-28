/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:48:02 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/27 17:13:16 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_conversion(int fd, char co, va_list arg)
{
	if (co == 'c')
		return (ft_printchar(fd, va_arg(arg, int)));
	else if (co == 's')
		return (ft_printstr(fd, va_arg(arg, char *)));
	else if (co == 'p')
		return (ft_printptr(fd, va_arg(arg, void *)));
	else if (co == 'd' || co == 'i')
		return (ft_putnbr_base_fd(fd, va_arg(arg, int), "0123456789"));
	else if (co == '%')
		return (ft_printprcnt(fd));
	else if (co == 'u')
		return (ft_putnbr_base_fd(fd, va_arg(arg, unsigned int), "0123456789"));
	else if (co == 'x')
		return (
			ft_putnbr_base_fd(fd, va_arg(arg, unsigned int), "0123456789abcdef"));
	else if (co == 'X')
		return (
			ft_putnbr_base_fd(fd, va_arg(arg, unsigned int), "0123456789ABCDEF"));
	return (0);
}

int	ft_fprintf(int fd, const char *str, ...)
{
	va_list		arg;
	int			i;
	int			counter;

	if (!str || !fd)
		return (-1);
	i = 0;
	counter = 0;
	va_start(arg, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			if (!ft_strchr("cspdiuxX%", str[i + 1]))
				return (-1);
			counter += print_conversion(fd, str[i + 1], arg);
			i += 2;
		}
		else
			counter += ft_printchar(fd, str[i++]);
	}
	va_end(arg);
	return (counter);
}

int	ft_printf(const char *str, ...)
{
	va_list		arg;
	int			i;
	int			counter;

	if (!str)
		return (-1);
	i = 0;
	counter = 0;
	va_start(arg, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			if (!ft_strchr("cspdiuxX%", str[i + 1]))
				return (-1);
			counter += print_conversion(1, str[i + 1], arg);
			i += 2;
		}
		else
			counter += ft_printchar(1, str[i++]);
	}
	va_end(arg);
	return (counter);
}
