/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   num_scan.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 14:09:15 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/17 14:09:15 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

t_num	*num_scan(t_num *stack, int idx)
{
	t_num	*num;
	int		_idx;

	if (!stack || idx < 0)
		return (NULL);
	_idx = 0;
	num = stack;
	while (num && _idx != idx)
	{
		num = num->next;
		_idx++;
	}
	return (num);
}
