/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   num_new.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 14:09:19 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/17 14:09:19 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_num	*num_new(int n)
{
	t_num	*num;

	num = malloc(sizeof(t_num));
	if (!num)
		return (NULL);
	num->num = n;
	num->next = NULL;
	num->prev = NULL;
	return (num);
}
