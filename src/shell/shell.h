/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:40:03 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/14 10:49:21 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../buildins/pwd/pwd.h"
# include "../buildins/exit/exit.h"
# include "../exe/exe.h"
# include "../includes/types.h"
# include "../includes/CONSTANTS.h"
# include "../libft/libft.h"
# include "../malloc_list/malloc_list.h"
# include "../parser/parser.h"
# include "../signals/signals.h"

void	start_shell(t_app *app);

#endif
