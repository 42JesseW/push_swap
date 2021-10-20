/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checks.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 14:09:06 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/17 14:09:06 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

/*
** Optimizes the following sequence:
**  - [ 5 4 3 2 1 ] -> [ 4 5 1 2 3 ] : 13 instructions -> 8 instructions
**  - [ 4 3 2 1 5 ] -> [ 3 4 5 1 2 ] : 14 instructions -> 8 instructions
**
**	Only works for stack of size 5
*/
bool	check_fulldesc_optimization(t_num **ab, int len, bool write_stdout)
{
	if (num_len(ab[0]) != 5)
		return (false);
	if (is_sorted(ab[0], CHECK_ALL, false, true)
		|| (is_sorted(ab[0], len - 1, false, true)
			&& ab[0]->num < ab[2]->num))
	{
		ins_exec(PUSHB, ab, write_stdout);
		ins_exec(PUSHB, ab, write_stdout);
		ins_exec(SWAP_BOTH, ab, write_stdout);
		ins_exec(REVERSE_ROTATEA, ab, write_stdout);
		ins_exec(PUSHA, ab, write_stdout);
		ins_exec(PUSHA, ab, write_stdout);
		return (true);
	}
	return (false);
}

bool	check_single_op(t_num **ab, int len, bool write_stdout)
{
	t_num	*num;

	num = num_scan(ab[0], 2);
	if ((!num && ab[0]->rank > ab[0]->next->rank)
		|| ((ab[0]->rank == ab[0]->next->rank + 1)
			&& (ab[0]->rank == num->rank - 1)
			&& (is_sorted(num, CHECK_ALL, true, true))))
	{
		ins_exec(SWAPA, ab, write_stdout);
		return (true);
	}
	if ((is_sorted(ab[0], len - 1, true, true))
		&& (ab[0]->rank == ab[2]->rank + 1))
	{
		ins_exec(REVERSE_ROTATEA, ab, write_stdout);
		return (true);
	}
	if ((is_sorted(ab[0]->next, CHECK_ALL, true, true))
		&& (ab[0]->rank == ab[2]->rank + 1))
	{
		ins_exec(ROTATEA, ab, write_stdout);
		return (true);
	}
	return (false);
}
