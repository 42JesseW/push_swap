#include "catch.hpp"
#include <random>

extern "C" {
	#include <push_swap.h>
}

static void	num_add_front(t_num **stack, t_num *num)
{
	if (!stack)
		return;
	else if (!(*stack))
		*stack = num;
	else
	{
		num->next = *stack;
		(*stack)->prev = num;
		*stack = num;
	}
}

static void	init_ab_stacks_random(t_num **ab, int size)
{
	std::random_device			randomSeed;
	std::default_random_engine	random(randomSeed());
	t_num						*num;

	ab[0] = ab[1] = ab[2] = ab[3] = nullptr;
	for (int i = 0; i < size; i++)
	{
		num = num_new(static_cast<int>((random() % (INT_MAX - 1) + 1)));
		num_add_front(ab, num);
		if (i == 0)
			ab[2] = num;
	}
    init_stack_ptr_set_rank(ab);
}

static void init_ab_stacks_sorted(t_num **ab, int size, bool asc)
{
    t_num   *num;

    ab[0] = ab[1] = ab[2] = ab[3] = nullptr;
    if (asc)
    {
        for (int i = (size - 1); i >= 0; i--)
        {
            num = num_new(i);
            num_add_front(ab, num);
            if (i == (size - 1))
                ab[2] = num;
        }
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            num = num_new(i);
            num_add_front(ab, num);
            if (i == 0)
                ab[2] = num;
        }
    }
    init_stack_ptr_set_rank(ab);
}

static void init_ab_stacks_int_arr(t_num **ab, int *arr, int size)
{
    t_num   *num;

    ab[0] = ab[1] = ab[2] = ab[3] = nullptr;
    for (int i = 0; i < size; i++)
    {
        num = num_new(arr[i]);
        num_add_front(ab, num);
        if (i == 0)
            ab[2] = num;
    }
    init_stack_ptr_set_rank(ab);
}

TEST_CASE("is_sorted") {

	SECTION("check empty stacks") {
        t_num   *ab[4];

        ab[0] = ab[1] = ab[2] = ab[3] = NULL;
        REQUIRE(is_sorted(ab[0], CHECK_ALL, true, true));
        REQUIRE(is_sorted(ab[0], CHECK_ALL, false, true));
	}

	SECTION("check sorted stacks") {
        t_num   *ab[4];

        init_ab_stacks_sorted(ab, 10, true);
        REQUIRE(is_sorted(ab[0], CHECK_ALL, true, true));
        num_free_all(ab[0]);
        init_ab_stacks_sorted(ab, 10, false);
        REQUIRE(is_sorted(ab[0], CHECK_ALL, false, true));
	}

	SECTION("check unsorted stacks") {
        t_num   *ab[4];

        init_ab_stacks_random(ab, 10);
        REQUIRE(!is_sorted(ab[0], CHECK_ALL, true, true));
        REQUIRE(!is_sorted(ab[0], CHECK_ALL, false, true));
        num_free_all(ab[0]);
        init_ab_stacks_sorted(ab, 10, true);
        REQUIRE(!is_sorted(ab[0], CHECK_ALL, false, true));
        num_free_all(ab[0]);
        init_ab_stacks_sorted(ab, 10, false);
        REQUIRE(!is_sorted(ab[0], CHECK_ALL, true, true));
	}

	SECTION("check with n len check") {
	    // TODO
	}

}

TEST_CASE("is_sorted_prerotate") {

	SECTION("check empty stacks") {
		t_num	*ab[4];

		ab[0] = ab[1] = ab[2] = ab[3] = NULL;
		REQUIRE(is_sorted_prerotate(ab[0], true) == false);
		REQUIRE(is_sorted_prerotate(ab[0], false) == false);
		REQUIRE(is_sorted_prerotate(ab[1], true) == false);
		REQUIRE(is_sorted_prerotate(ab[1], false) == false);
	}

	SECTION("check stack with one item") {
		t_num	*ab[4];

		init_ab_stacks_random(ab, 1);
		REQUIRE(is_sorted_prerotate(ab[0], true) == false);
		REQUIRE(is_sorted_prerotate(ab[0], false) == false);
		REQUIRE(is_sorted_prerotate(ab[1], true) == false);
		REQUIRE(is_sorted_prerotate(ab[1], false) == false);
	}

	SECTION("check fully sorted or unsorted (prerotate) stack") {
		t_num	*ab[4];

		init_ab_stacks_sorted(ab, 10, true);
		REQUIRE(is_sorted_prerotate(ab[0], true) == false);
		ins_exec(SWAPA, ab, false);
		REQUIRE(is_sorted_prerotate(ab[0], true) == false);
		for (int i = 0; i < 4; i++)
			ins_exec(PUSHB, ab, false);
		REQUIRE(is_sorted_prerotate(ab[1], false) == false);
		ins_exec(ROTATEB, ab, false);
		REQUIRE(is_sorted_prerotate(ab[1], false) == false);
	}

	SECTION("weird edge cases") {

	    SECTION("5 1 2 4 3") {
            t_num   *ab[4];
            int     arr[] = {3, 4, 2, 1, 5};

            init_ab_stacks_int_arr(ab, arr, 5);
            REQUIRE(is_sorted_prerotate(ab[0], true) == false);
	    }
	}

	SECTION("check sorted (prerotate) stacks") {
		t_num	*ab[4];
		int		size;

		size = 6;
		init_ab_stacks_sorted(ab, size, true);
		ins_exec(ROTATEA, ab, false);
		REQUIRE(is_sorted_prerotate(ab[0], true) == true);
		for (int i = 0; i < (size * 0.5); i++)
			ins_exec(REVERSE_ROTATEA, ab, false);
		REQUIRE(is_sorted_prerotate(ab[0], true) == true);
		for (int i = 0; i < size; i++)
			ins_exec(PUSHB, ab, false);
		REQUIRE(is_sorted_prerotate(ab[1], false) == true);
		for (int i = 0; i < (size * 0.5); i++)
			ins_exec(REVERSE_ROTATEB, ab, false);
		REQUIRE(is_sorted_prerotate(ab[1], false) == true);
		ins_exec(REVERSE_ROTATEB, ab, false);
		REQUIRE(is_sorted_prerotate(ab[1], false) == true);
	}
}

TEST_CASE("sort_prerotate_get_op") {

    SECTION("Check basic cases") {
        t_num	*ab[4];
        int		size;

        size = 6;
        init_ab_stacks_sorted(ab, size, true);
        ins_exec(ROTATEA, ab, false);
        REQUIRE(ft_strcmp(sort_prerotate_get_op(ab[0], 'a', true), REVERSE_ROTATEA) == 0);
        ins_exec(ROTATEA, ab, false);
        REQUIRE(ft_strcmp(sort_prerotate_get_op(ab[0], 'a', true), REVERSE_ROTATEA) == 0);
        ins_exec(ROTATEA, ab, false);
        REQUIRE(ft_strcmp(sort_prerotate_get_op(ab[0], 'a', true), REVERSE_ROTATEA) == 0);
        ins_exec(ROTATEA, ab, false);
        REQUIRE(ft_strcmp(sort_prerotate_get_op(ab[0], 'a', true), ROTATEA) == 0);

        num_free_all(ab[0]);
        init_ab_stacks_sorted(ab, 1, true);
        REQUIRE(ft_strcmp(sort_prerotate_get_op(ab[0], 'a', true), ROTATEA) == 0);
    }

    SECTION("Check edge cases") {
        t_num	*ab[4];
        int		size;

        // uneven stack length
        size = 5;
        init_ab_stacks_sorted(ab, size, true);
        // exactly in the middle
        for (int i = 0; i < 2; i++)
            ins_exec(ROTATEA, ab, false);
        REQUIRE(ft_strcmp(sort_prerotate_get_op(ab[0], 'a', true), REVERSE_ROTATEA) == 0);
        ins_exec(ROTATEA, ab, false);
        REQUIRE(ft_strcmp(sort_prerotate_get_op(ab[0], 'a', true), ROTATEA) == 0);
    }
}

TEST_CASE("sort_prerotate") {

    SECTION("Check empty") {
        t_num   *ab[4];

        ab[0] = ab[1] = ab[2] = ab[3] = NULL;
        sort_prerotate(ab, 'a', true, false);
        REQUIRE(ab[0] == NULL);
        sort_prerotate(ab, 'a', false, false);
        REQUIRE(ab[0] == NULL);
        sort_prerotate(ab, 'b', true, false);
        REQUIRE(ab[0] == NULL);
        sort_prerotate(ab, 'b', false, false);
        REQUIRE(ab[0] == NULL);
    }

    SECTION("Check simple sorting") {
        t_num	*ab[4];
        int		size;

        size = 6;
        init_ab_stacks_sorted(ab, size, true);
        ins_exec(ROTATEA, ab, false);
        sort_prerotate(ab, 'a', true, false);
        REQUIRE(is_sorted(ab[0], CHECK_ALL, true, true));
        for (int i = 0; i < 2; i++)
            ins_exec(ROTATEA, ab, false);
        sort_prerotate(ab, 'a', true, false);
        REQUIRE(is_sorted(ab[0], CHECK_ALL, true, true));
        for (int i = 0; i < 3; i++)
            ins_exec(ROTATEA, ab, false);
        sort_prerotate(ab, 'a', true, false);
        REQUIRE(is_sorted(ab[0], CHECK_ALL, true, true));
        for (int i = 0; i < 4; i++)
            ins_exec(ROTATEA, ab, false);
        sort_prerotate(ab, 'a', true, false);
        REQUIRE(is_sorted(ab[0], CHECK_ALL, true, true));
    }
}
