/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:01:25 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/19 11:07:36 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "exe_test.h"

int main(int argc, char **argv, char *envp[]) {
	t_app *app = init_shell(envp);
	ft_printf("RUNNING EXE TESTS\n");

	// Test 1: "pwd"
	char *test_args_1[] = {"pwd", NULL};
	t_io_file test_infile = {0, 0};
	t_io_file test_outfile = {1, 0};
	t_cmd_info test_1 = {test_infile, test_outfile, test_args_1, BIN};

	// Test 2: "unknown"
	char *test_args_2[] = {"unknown", NULL};
	t_cmd_info test_2 = {test_infile, test_outfile, test_args_2, BIN};

	// Test 3: "ls" with output to file
	int fd = open("test_out", O_RDWR | O_CREAT, 0644);
	if (fd == -1) {
		perror("Error opening test_out");
		free_malloc_list(app);
		return 1;
	}

	char *test_args_3[] = {"ls", NULL};
	t_io_file test_outfile_3 = {fd, 0};
	t_cmd_info test_3 = {test_infile, test_outfile_3, test_args_3, BIN};

	// Execute tests
	ft_printf("Test 1: pwd, stdout\n");
	exe(app, &test_1);

	ft_printf("Test 2: unknown, stdout\n");
	exe(app, &test_2);

	ft_printf("Test 3: ls, test_out\n");
	exe(app, &test_3);

	// Cleanup
	close(fd);
	free_malloc_list(app);
	while (0)
		argv[argc] = 0;

	return 0;
}
