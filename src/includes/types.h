/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:49:38 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/25 15:08:47 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H
# include "../libft/libft.h"

typedef struct s_app
{
	t_list	*malloc_list;
	char	**envp;
}	t_app;

typedef enum e_cmd_type {
	UNDEFINED = 0,
	LOGICAL = 1,
	PIPE = 2,
	BIN = 3
}	t_cmd_type;

typedef struct s_cmd_info
{
	int			infile;
	int			outfile;
	char		**args;
	t_cmd_type	type;
}	t_cmd_info;
#endif
