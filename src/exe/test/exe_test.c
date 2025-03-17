/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:01:25 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/17 12:04:35 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../exe.h"

int	main(void)
{
	ft_printf("RUNNING EXE TESTS\n");
	char		*test_1_args[] = {"pwd", NULL};
	t_cmd_info	test_1 = {0, 1, test_1_args, BIN};

	exe(&test_1);
}
