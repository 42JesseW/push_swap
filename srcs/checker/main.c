/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 14:10:34 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/17 14:10:35 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

static t_instruct	g_instructs[] = {
	(t_instruct){.ins = SWAPA, .func = ins_swapa},
	(t_instruct){.ins = SWAPB, .func = ins_swapb},
	(t_instruct){.ins = SWAP_BOTH, .func = ins_swap_both},
	(t_instruct){.ins = PUSHA, .func = ins_pusha},
	(t_instruct){.ins = PUSHB, .func = ins_pushb},
	(t_instruct){.ins = ROTATEA, .func = ins_rotatea},
	(t_instruct){.ins = ROTATEB, .func = ins_rotateb},
	(t_instruct){.ins = ROTATE_BOTH, .func = ins_rotate_both},
	(t_instruct){.ins = REVERSE_ROTATEA, .func = ins_rrotatea},
	(t_instruct){.ins = REVERSE_ROTATEB, .func = ins_rrotateb},
	(t_instruct){.ins = REVERSE_ROTATE_BOTH, .func = ins_rrotate_both},
	(t_instruct){.ins = NULL, .func = NULL}
};

void	exit_checker(t_num **ab, int *nums, bool err)
{
	int		exit_code;

	exit_code = EXIT_SUCCESS;
	if (err)
	{
		write(STDERR_FILENO, "Error\n", 7);
		exit_code = EXIT_FAILURE;
	}
	if (nums)
		free(nums);
	if (ab[1])
	{
		num_free_all(ab[1]);
		num_free_all(ab[0]);
	}
	exit(exit_code);
}

/*
** read_stdin_ops() reads instructions from
** STDIN untill EOF (CTRL + D). Instructions
** must match any of the possible instructions:
**
**	{sa} {sb} {ss} {pa} {pb} {ra} {rb} {rr}
**			{rra}	{rrb}	{rrr}
** If {op} is still NULL on return, an error
*/

bool	read_stdin_ops(char **op)
{
	char	*line;
	int		ret;
	int		idx;

	ret = get_next_line(STDIN_FILENO, &line);
	*op = line;
	if (ret == 0 || ret == -1)
		return (false);
	idx = 0;
	while (g_instructs[idx].ins)
	{
		if (ft_strcmp(line, g_instructs[idx].ins) == 0)
			break ;
		idx++;
	}
	if ((idx + 1) == (sizeof(g_instructs) / sizeof(t_instruct)))
	{
		free(line);
		*op = NULL;
		return (false);
	}
	return (true);
}

/*
** main() takes arguments via {*argv[]}.
** arguments passed must be integers, either
** negative or positive.
**	- No non-digit characters are allowed
**	  excluding the minus sign (45).
**	- No duplicate numbers are allowed
*/

int	main(int argc, char *argv[])
{
	t_num	*ab[4];
	int		*nums;
	int		idx;
	char	*op;

	ab[1] = NULL;
	if (argc < 2 || !valid_digits(argc, argv))
		exit_checker(ab, NULL, (argc >= 2));
	nums = malloc((argc - 1) * sizeof(int));
	if (!nums || has_duplicates(nums, argc - 1, argv + 1))
		exit_checker(ab, nums, true);
	if (!load_stack(ab, nums, argc - 1))
		exit_checker(ab, nums, true);
	while (read_stdin_ops(&op))
	{
		idx = 0;
		while (g_instructs[idx].ins)
		{
			if (ft_strcmp(op, g_instructs[idx].ins) == 0)
				g_instructs[idx].func(ab);
			idx++;
		}
	}
	return (check(ab, nums, op));
}
