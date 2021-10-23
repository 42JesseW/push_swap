/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ins_exec.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 14:09:56 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/17 14:09:56 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

static t_instruct	g_instructs[] = {
	(t_instruct){.ins = SWAPA, .func = ins_swapa},
	(t_instruct){.ins = SWAPB, .func = ins_swapb},
	(t_instruct){.ins = SWAP_BOTH, .func = ins_swap_both},
	(t_instruct){.ins = PUSHA, .func = ins_pusha},
	(t_instruct){.ins = PUSHB, .func = ins_pushb},
	(t_instruct){.ins = ROTATEA, .func = ins_rotatea},
	(t_instruct){.ins = ROTATEB, .func = ins_rotateb},
	(t_instruct){.ins = ROTATE_BOTH, .func = ins_rotate_both},
	(t_instruct){.ins = REVERSE_ROTATEA, .func = ins_rrotatea},
	(t_instruct){.ins = REVERSE_ROTATEB, .func = ins_rrotateb},
	(t_instruct){.ins = REVERSE_ROTATE_BOTH, .func = ins_rrotate_both},
	(t_instruct){.ins = NULL, .func = NULL}
};

void	ins_exec(char *op, t_num **ab, bool write_stdout)
{
	int	idx;

	idx = 0;
	while (g_instructs[idx].ins)
	{
		if (ft_strcmp(op, g_instructs[idx].ins) == 0)
		{
			g_instructs[idx].func(ab);
			if (write_stdout)
				ft_printf("%s\n", op);
			break ;
		}
		idx++;
	}
}
