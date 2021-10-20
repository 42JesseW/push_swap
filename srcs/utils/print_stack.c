/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_stack.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 14:07:29 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/17 14:08:18 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

void	print_stack(t_num *stack, char ab)
{
	t_num	*num;

	num = stack;
	ft_printf("[Stack %c]\n", ab);
	while (num != NULL)
	{
		ft_printf("  %d: %d\n", num->num, num->rank);
		num = num->next;
	}
}
