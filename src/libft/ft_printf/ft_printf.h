/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:23:22 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/27 17:11:46 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft.h"
# include <stdio.h>
# include <stdarg.h>

int		ft_printf(const char *str, ...);
int		ft_fprintf(int fd, const char *str, ...);

// ft_printf_utils.c
int		ft_printchar(int fd, char c);
int		ft_printstr(int fd, char *str);
int		ft_printptr(int fd, void *ptr);
void	ft_putull_base(unsigned long long nbr,
			char *base, int cnt, int radix);

// ft_print_vars.c
int		ft_printnbr(int fd, long long nbr);
int		ft_printprcnt(int fd);
int		ft_print_ptr(int fd, unsigned long long ptr);

// ft_putnbr_base_fd
void	ft_putull_base_fd(int fd, unsigned long long nbr,
			char *base, int cnt);
int		ft_get_base(char *base);
int		ft_putnbr_base_fd(int fd, long long nbr, char *base);

#endif
