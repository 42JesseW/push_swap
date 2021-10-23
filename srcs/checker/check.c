/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 14:10:38 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/17 14:10:39 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

static int	check_stack(t_num *ab)
{
	t_num	*num;
	t_num	*tmp;

	num = ab;
	while (num)
	{
		if (!num->next)
			break ;
		tmp = num;
		if (tmp->num > num->next->num)
			break ;
		num = num->next;
	}
	return (num->next == NULL);
}

int	check(t_num *ab[2], int *nums, const char *op)
{
	int	exit_code;

	free(nums);
	exit_code = EXIT_SUCCESS;
	if (!op)
	{
		write(STDERR_FILENO, "Error\n", 6);
		exit_code = EXIT_FAILURE;
	}
	else if (ab[1] || !check_stack(ab[0]))
		write(STDOUT_FILENO, "KO\n", 3);
	else
		write(STDOUT_FILENO, "OK\n", 3);
	num_free_all(ab[0]);
	num_free_all(ab[1]);
	return (exit_code);
}
