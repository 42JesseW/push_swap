# Allowed functions:
#	* write
#	* read
#	* malloc
#	* free
#	* exit

NAME =				push_swap checker

CFLAGS =			-Wall -Werror -Wextra

LIBFTDIR = 			libft
LIBFTLIB = 			libft.a

INCLUDES =			includes

SRC_DIR = 			srcs

UTILS_DIR =			$(addprefix $(SRC_DIR)/, utils)
SRCS_UTILS =		has_duplicates.c \
					load_stack.c \
					print_stack.c \
					valid_digits.c \
					sort/is_sorted.c \
					sort/sort_prerotate.c \
					num/num_new.c \
					num/num_len.c \
					num/num_at.c \
					num/num_scan.c \
					num/num_free_all.c \
					ins/ins_push.c \
					ins/ins_swap.c \
					ins/ins_rotate.c \
					ins/ins_rrotate.c \
					ins/ins_exec.c \
					ins/ins_get_stack_op.c \
					optimize/checks.c \
					optimize/is_swapa_optimizable.c \
					ft_atol.c
OBJ_UTILS =			$(addprefix $(UTILS_DIR)/, $(SRCS_UTILS:.c=.o))

CHECKER_DIR = 		$(addprefix $(SRC_DIR)/, checker)
SRCS_CHECKER = 		main.c \
					check.c
OBJ_CHECKER = 		$(addprefix $(CHECKER_DIR)/, $(SRCS_CHECKER:.c=.o))

PUSH_SWAP_DIR = 	$(addprefix $(SRC_DIR)/, push_swap)
SRCS_PUSH_SWAP =	main.c \
                    init_stack_ptr.c \
                    push_swap_small.c \
                    push_swap_large.c \
					push_swap.c
OBJ_PUSH_SWAP = 	$(addprefix $(PUSH_SWAP_DIR)/, $(SRCS_PUSH_SWAP:.c=.o))

LIBS =				$(addprefix -l, $(subst lib,,$(subst .a,,$(LIBFTLIB))))

UNAME_S =			$(shell uname -s)

ifeq ($(UNAME_S), Darwin)
	P = 			\x1b[35m
	B = 			\x1b[34m
	Y = 			\x1b[33m
	G = 			\x1b[32m
	R = 			\x1b[31m
	W = 			\x1b[0m
else ifeq ($(UNAME_S), Linux)
	P = 			\033[35m
	B = 			\033[34m
	Y = 			\033[33m
	G = 			\033[32m
	R = 			\033[31m
	W = 			\033[0m
endif

all: $(NAME)

$(word 1, $(NAME)): $(OBJ_UTILS) $(OBJ_PUSH_SWAP) $(LIBFTLIB)
	@echo "$(Y)building push_swap..$(W)"
	@$(CC) -I$(INCLUDES) $(CFLAGS) $(OBJ_UTILS) $(OBJ_PUSH_SWAP) -L. $(LIBS) -o $@

$(word 2, $(NAME)): $(OBJ_UTILS) $(OBJ_CHECKER) $(LIBFTLIB)
	@echo "$(Y)building checker..$(W)"
	@$(CC) -I$(INCLUDES) $(CFLAGS) $(OBJ_UTILS) $(OBJ_CHECKER) -L. $(LIBS) -o $@

$(LIBFTLIB):
	@echo "\n$(G)Making $(LIBFTLIB) static lib$(W)"
	@make --directory=$(LIBFTDIR)
	@cp $(LIBFTDIR)/$(LIBFTLIB) .

%.o: %.c
	@echo "$(Y)Compiling $< to $@...$(W)"
	@$(CC) -I$(INCLUDES) -c $(CFLAGS) -o $@ $<

clean:
	@echo "$(R)Cleaning up obj files and random .txt files...$(W)"
	@echo "$(OBJ_CHECKER) -> $(OBJ_PUSH_SWAP) -> $(OBJ_UTILS)"
	rm -vf $(OBJ_CHECKER) $(OBJ_PUSH_SWAP) $(OBJ_UTILS)

fclean: clean
	@echo "$(R)Cleaning up $(NAME)...$(W)"
	@rm -vf $(NAME) $(LIBFTLIB)
	@make --directory=$(LIBFTDIR) fclean

re: fclean all
