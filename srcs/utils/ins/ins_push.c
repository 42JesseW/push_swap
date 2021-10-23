/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ins_push.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 14:09:50 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/17 14:09:50 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** push a - take the first element at
** the top of b and put it at the top
** of a. Do nothing if b is empty
*/

void	ins_pusha(t_num **head)
{
	t_num	*num;

	if (head[1])
	{
		num = head[1];
		if (num->next)
			num->next->prev = NULL;
		head[1] = num->next;
		if (!head[1])
			head[3] = NULL;
		num->next = head[0];
		if (num->next)
			num->next->prev = num;
		if (!head[0])
			head[2] = num;
		head[0] = num;
	}
}

/*
** push b - take the first element at
** the top of a and put it at the top
** of b. Do nothing if a is empty
*/

void	ins_pushb(t_num **head)
{
	t_num	*num;

	if (head[0])
	{
		num = head[0];
		if (num->next)
			num->next->prev = NULL;
		head[0] = num->next;
		if (!head[0])
			head[2] = NULL;
		num->next = head[1];
		if (num->next)
			num->next->prev = num;
		if (!head[1])
			head[3] = num;
		head[1] = num;
	}
}
