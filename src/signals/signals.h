/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:54:49 by jhelbig           #+#    #+#             */
/*   Updated: 2025/04/08 13:56:24 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H
# include <stdio.h>
# include "../includes/types.h"
# include "../includes/CONSTANTS.h"
# include <readline/readline.h>
# include <readline/history.h>

void	handle_signal_shell(int sig);
void	init_sa_shell(t_app *app);

#endif
