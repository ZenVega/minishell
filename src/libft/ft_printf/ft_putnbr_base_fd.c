/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:02:03 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/27 17:16:06 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_get_base(char *base)
{
	int	counter;
	int	compare_counter;

	counter = 0;
	while (base[counter])
	{
		if (base[counter] == '-' || base[counter] == '+')
			return (0);
		compare_counter = counter - 1;
		while (compare_counter >= 0)
		{
			if (base[counter] != base[compare_counter])
				compare_counter--;
			else
				return (0);
		}
		counter++;
	}
	if (counter < 1)
		return (0);
	return (counter);
}

void	ft_putull_base_fd(int fd, unsigned long long nbr,
		char *base, int cnt)
{
	unsigned long long	div;
	unsigned long long	mod;
	int					radix;

	radix = ft_get_base(base);
	div = nbr / radix;
	mod = nbr % radix;
	if (div)
	{
		cnt++;
		ft_putull_base_fd(fd, div, base, cnt);
	}
	write(fd, &base[mod], 1);
}

int	ft_putnbr_base_fd(int fd, long long nbr, char *base)
{
	unsigned long long	len;
	unsigned long long	temp;
	int					radix;

	len = 0;
	if (nbr == 0)
		len++;
	if (nbr < 0)
	{
		write(1, "-", fd);
		nbr = -nbr;
		len++;
	}
	temp = nbr;
	radix = ft_get_base(base);
	if (!radix)
		return (0);
	while (temp)
	{
		temp /= radix;
		len++;
	}
	ft_putull_base_fd(fd, nbr, base, 0);
	return ((int)len);
}
