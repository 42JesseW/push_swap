/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_sorted.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 14:08:51 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/17 14:08:52 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

bool	is_sorted(t_num *stack, int n, bool asc, bool ranked)
{
	t_num	*num;
	int		count;
	int		check_amount;

	if (!stack)
		return (true);
	count = 1;
	num = stack;
	check_amount = num_len(stack);
	if (n >= 0)
		check_amount = n;
	while (num->next && count < check_amount)
	{
		if (!ranked && ((asc && num->num > num->next->num)
				|| (!asc && num->num < num->next->num)))
			return (false);
		if (ranked && ((asc && num->rank != num->next->rank - 1)
				|| (!asc && num->rank != num->next->rank + 1)))
			return (false);
		num = num->next;
		count++;
	}
	return (true);
}

/*
** check if stack consists of two parts
** which are only to be rotated correctly
*/

bool	is_sorted_prerotate(t_num *stack, bool asc)
{
	t_num	*num;
	bool	has_passed;

	if (is_sorted(stack, CHECK_ALL, true, true)
		|| is_sorted(stack, CHECK_ALL, false, true))
		return (false);
	num = stack;
	has_passed = false;
	while (num)
	{
		if (asc && has_passed && (num->num > stack->num
				|| (num->next && num->num > num->next->num)))
			return (false);
		if (asc && !has_passed && num->next && num->num > num->next->num)
			has_passed = true;
		if (!asc && has_passed && (num->num < stack->num
				|| (num->next && num->num < num->next->num)))
			return (false);
		if (!asc && !has_passed && num->next && num->num < num->next->num)
			has_passed = true;
		num = num->next;
	}
	return (has_passed);
}
