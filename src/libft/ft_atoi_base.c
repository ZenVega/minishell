/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:42:03 by uschmidt          #+#    #+#             */
/*   Updated: 2024/11/18 18:20:27 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_base(const char *nptr, char *base)
{
	int					neg;
	unsigned long long	result;
	int					radix;

	radix = ft_get_base(base);
	if (!radix)
		return (0);
	neg = 1;
	result = 0;
	while (*nptr == ' ' || *nptr == '\f' || *nptr == '\n'
		|| *nptr == '\r' || *nptr == '\t' || *nptr == '\v')
		nptr++;
	if (nptr[0] == '0' && (nptr[1] == 'x' || nptr[1] == 'X'))
		nptr += 2;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr == '-')
			(free(0), nptr++, neg = -1);
	while (*nptr)
	{
		result = result * radix + (ft_strchr(base, ft_tolower(*nptr)) - base);
		nptr++;
	}
	return (result * neg);
}
