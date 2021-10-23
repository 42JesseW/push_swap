/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   num_len.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 14:09:23 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/17 14:09:24 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

int	num_len(t_num *stack)
{
	t_num	*num;
	int		len;

	len = 0;
	num = stack;
	while (num)
	{
		num = num->next;
		len++;
	}
	return (len);
}
