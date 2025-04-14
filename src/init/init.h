/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:05:19 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/25 13:51:41 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "../includes/types.h"
# include "../error/error.h"
# include "../malloc_list/malloc_list.h"

t_app	*init_shell(char *envp[]);

#endif
