/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_swapa_optimizable.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 14:09:10 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/17 14:09:10 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

/*
** Checks for the following two sequences to be optimized:
**  - [ 4 5 3 2 1 ] -> [ 5 4 3 2 1 ] : 13 instructions -> 9 instructions
**  - [ 1 5 3 2 4 ] -> [ 5 1 3 2 4 ] : 13 instructions -> 5 instructions
**
** Resulting sequences have an already
** optimized routine which they'll fall
** into after being swapped.
*/
bool	is_swapa_optimizable(t_num **ab)
{
	if (is_sorted(num_scan(ab[0], 2), 3, false, true)
		&& ab[0]->next->rank == num_scan(ab[0], 2)->rank + 2)
		return (true);
	if (ab[0]->rank == 1
		&& ab[0]->next->rank == num_scan(ab[0], 2)->rank + 2
		&& ab[2]->rank == ab[2]->prev->rank + 2)
		return (true);
	return (false);
}
