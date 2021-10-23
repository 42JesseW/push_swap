/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap_small.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 14:10:27 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/17 14:10:28 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

/*
** The ranked search using stack B can
** only start pushing back to A if one
** of two conditions is met:
**  1.  A is sorted (ranked) in ascending order
**  &&  B is sorted (ranked) in descending order
**  2.  B is not empty and the first item on A's
**	    rank is 1 higher then the first item on B.
**  &&  A from the second number is sorted (ranked) ascending
**  &&  B is sorted (ranked) in descending order
*/
static bool	ranked_check_pusha(t_num **ab)
{
	if ((ab[1] && ab[0]->rank == ab[1]->rank + 1)
		&& is_sorted(ab[0]->next, CHECK_ALL, true, true)
		&& is_sorted(ab[1], CHECK_ALL, false, true))
		return (true);
	if (is_sorted(ab[0], CHECK_ALL, true, true)
		&& is_sorted(ab[1], CHECK_ALL, false, true))
		return (true);
	return (false);
}

void	push_swap_small_ranked_rotate(t_num **ab, bool write_stdout)
{
	int		idx;
	int		len;
	char	*op;

	len = num_len(ab[0]);
	op = ins_get_stack_op('a', ROTATE);
	idx = num_at(ab[0], ab[1]->rank + 1);
	if (idx > (len * 0.5))
		op = ins_get_stack_op('a', REVERSE_ROTATE);
	while (ab[0]->rank != ab[1]->rank + 1)
		ins_exec(op, ab, write_stdout);
}

/*
** Ranked search but using stack B
**  - push to B in descending order
**  - push back to A
**
**  [conditions]
**  - Top most ranked and second most ranked
**	  can not be pushed if B is empty.
**  - If not the right number at the top of
**	  stack A, get the index of the wanted
**	  number using its rank and rotate this
**	  to the top as efficient as possible.
*/
void	push_swap_small_ranked(t_num **ab, int len, bool write_stdout)
{
	while (!is_sorted_prerotate(ab[0], true) || ab[1])
	{
		if (ranked_check_pusha(ab))
		{
			while (ab[1])
				ins_exec(PUSHA, ab, write_stdout);
		}
		else if (!check_single_op(ab, len, write_stdout))
		{
			if (!ab[1] && (ab[0]->rank == len || ab[0]->rank == len - 1))
				ins_exec(ROTATEA, ab, write_stdout);
			else if (!ab[1] || ab[0]->rank == ab[1]->rank + 1)
				ins_exec(PUSHB, ab, write_stdout);
			else
				push_swap_small_ranked_rotate(ab, write_stdout);
		}
		if (is_sorted(ab[0], CHECK_ALL, true, true) && !ab[1])
			break ;
	}
}

void	push_swap_small_three(t_num **ab, bool write_stdout)
{
	if (ab[0]->rank == ab[2]->rank - 1 || ab[0]->rank == ab[2]->rank + 1)
		ins_exec(SWAPA, ab, write_stdout);
	else if (ab[0]->rank == ab[2]->rank - 1)
		ins_exec(REVERSE_ROTATEA, ab, write_stdout);
	else
		ins_exec(ROTATEA, ab, write_stdout);
}

/*
**
**  DESCRIPTION:
**   - this function takes the same input as push_swap so the
**	 same conditions apply here. The difference is that this
**	 function is only called when the stack has length <= 5
**
**  - Algorithm:
**	  - If stack A is already sorted but only needs to be
**		rotated using ROTATEA or REVERSE_ROTATEA. Use the
**		{is_sorted_prerotate()} to check for this case and
**		use {sort_prerotate()} to rotate most efficiently.
**	  - If stack A has a length smaller then or equal to 3,
**		then use the {push_swap_small_three()} routine to
**		safely swap this using only three checks.
**
*/

void	push_swap_small(t_num **ab, bool write_stdout)
{
	int	len;

	len = num_len(ab[0]);
	while (!is_sorted(ab[0], CHECK_ALL, true, true) || ab[1])
	{
		if (check_single_op(ab, len, write_stdout))
			break ;
		if (is_sorted_prerotate(ab[0], true) && !ab[1])
		{
			sort_prerotate(ab, 'a', true, write_stdout);
			break ;
		}
		if (len <= 3)
			push_swap_small_three(ab, write_stdout);
		else
		{
			if (is_swapa_optimizable(ab))
				ins_exec(SWAPA, ab, write_stdout);
			if (check_fulldesc_optimization(ab, len, write_stdout))
				continue ;
			push_swap_small_ranked(ab, len, write_stdout);
		}
	}
}
