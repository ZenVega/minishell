/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:41:58 by uschmidt          #+#    #+#             */
/*   Updated: 2024/11/19 09:42:53 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	ft_toupper(int c)
{
	int	offset;

	offset = 'a' - 'A';
	if (c >= 'a' && c <= 'z')
		return (c - offset);
	else
		return (c);
}
