#ifndef FT_PUSH_SWAP_H

# define FT_PUSH_SWAP_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include "../libft//includes/libft.h"
#include "../libft/includes/get_next_line.h"
#include "../libft/includes/printf.h"

# define SWAPA "sa"
# define SWAPB "sb"
# define SWAP_BOTH "ss"
# define PUSHA "pa"
# define PUSHB "pb"
# define ROTATEA "ra"
# define ROTATEB "rb"
# define ROTATE_BOTH "rr"
# define REVERSE_ROTATEA "rra"
# define REVERSE_ROTATEB "rrb"
# define REVERSE_ROTATE_BOTH "rrr"

# define CHECK_ALL -1

enum                e_ins
{
    SWAP,
    PUSH,
    ROTATE,
    REVERSE_ROTATE
};

struct              s_ins
{
    enum e_ins      ins;
    char            abc;
    char            *op;
};

typedef struct		s_num
{
	int				num;
	int             rank;
	struct s_num	*next;
	struct s_num	*prev;
}					t_num;

typedef struct		s_instruct
{
	char			*ins;
	void			(*func)(t_num **stacks);
}					t_instruct;

void				push_swap(t_num **ab, bool write_stdout);
void				push_swap_small(t_num **ab, bool write_stdout);
void				push_swap_large(t_num **ab, bool write_stdout);

long				ft_atol(const char *str);
bool				is_sorted(t_num *stack, int n, bool asc, bool ranked);
bool				is_sorted_prerotate(t_num *stack, bool asc);

bool				load_stack(t_num **ab, int *nums, int size);
void				print_stack(t_num *stack, char ab);

bool				has_duplicates(int *nums, int argc, char **argv);
bool				valid_digits(int argc, char **argv);
int					check(t_num *ab[2], int *nums, const char *op);

bool                check_fulldesc_optimization(t_num **ab, int len, bool write_stdout);
bool                check_single_op(t_num **ab, int len, bool write_stdout);
bool                is_swapa_optimizable(t_num **ab);

void				num_free_all(t_num *head);
t_num				*num_new(int n);
t_num               *num_scan(t_num *stack, int idx);
int                 num_at(t_num *stack, int rank);
int					num_len(t_num *stack);

void				ins_exec(char *op, t_num **ab, bool write_stdout);
void				ins_swapa(t_num **head);
void				ins_swapb(t_num **head);
void				ins_swap_both(t_num **head);
void				ins_pusha(t_num **head);
void				ins_pushb(t_num **head);
void				ins_rotatea(t_num **head);
void				ins_rotateb(t_num **head);
void				ins_rotate_both(t_num **head);
void				ins_rrotatea(t_num **head);
void				ins_rrotateb(t_num **head);
void				ins_rrotate_both(t_num **head);

char                *ins_get_stack_op(char ab, enum e_ins ins);

void                sort_prerotate(t_num **ab, char c, bool asc, bool write_stdout);
char                *sort_prerotate_get_op(t_num *stack, char ab, bool asc);

void	            init_stack_ptr(t_num **ab);
void                init_stack_ptr_set_rank(t_num **ab);

#endif
