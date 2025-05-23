/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:54:49 by jhelbig           #+#    #+#             */
/*   Updated: 2025/05/23 12:13:09 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H
# include <stdio.h>
# include "../includes/types.h"
# include "../includes/CONSTANTS.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>

extern int	g_global_signal;

void	handle_signal_shell(int sig);
void	init_sa_shell(t_app *app);

void	handle_signal_parent(int sig);
void	init_sa_child(t_app *app);
void	init_sa_parent(t_app *app);

#endif
