/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   load_stack.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 14:08:34 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/17 14:08:39 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

bool	load_stack(t_num **ab, int *nums, int size)
{
	t_num	*num;
	t_num	*tmp;
	int		idx;

	ab[0] = num_new(nums[0]);
	if (!ab[0])
		return (false);
	idx = 1;
	tmp = ab[0];
	while (idx < size)
	{
		num = num_new(nums[idx]);
		if (!num)
		{
			num_free_all(ab[0]);
			return (false);
		}
		num->prev = ab[0];
		ab[0]->next = num;
		ab[0] = num;
		idx++;
	}
	ab[0] = tmp;
	return (true);
}
