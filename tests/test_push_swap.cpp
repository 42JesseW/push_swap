#include "catch.hpp"

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

TEST_CASE("push_swap ranking numbers") {

    SECTION("numbers should be ranked appropriately") {
        t_num   *ab[4];
        int     n = 5;
        int     arr[n];
        int     temp;

        arr[0] = 5; arr[1] = 4; arr[2] = 3; arr[3] = 2; arr[4] = 1;
        for (int j = 1; j <= n; j++)
        {
            for (int i = 0; i < n-1; i++)
            {
                temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                init_ab_stacks_int_arr(ab, arr, n);
                for (t_num *num = ab[0]; num != NULL; num = num->next)
                    REQUIRE(num->num == num->rank);
                num_free_all(ab[0]);
            }
        }
    }
}

TEST_CASE("push_swap stack of 5 max numbers") {

    SECTION("5 numbers sorted prerotate"){

        SECTION("2 3 4 5 1") {
            t_num   *ab[4];
            int     arr[] = {1, 5, 4, 3, 2};

            init_ab_stacks_int_arr(ab, arr, 5);
            REQUIRE(num_len(ab[0]) == 5);
            push_swap(ab, false);
            REQUIRE(is_sorted(ab[0], CHECK_ALL, true, true));
        }

        SECTION("3 4 5 1 2") {
            t_num   *ab[4];
            int     arr[] = {2, 1, 5, 4, 3};

            init_ab_stacks_int_arr(ab, arr, 5);
            REQUIRE(num_len(ab[0]) == 5);
            push_swap(ab, false);
            REQUIRE(is_sorted(ab[0], CHECK_ALL, true, true));
        }

        SECTION("4 5 1 2 3") {
            t_num   *ab[4];
            int     arr[] = {3, 2, 1, 5, 4};

            init_ab_stacks_int_arr(ab, arr, 5);
            REQUIRE(num_len(ab[0]) == 5);
            push_swap(ab, false);
            REQUIRE(is_sorted(ab[0], CHECK_ALL, true, true));
        }

        SECTION("5 1 2 3 4") {
            t_num   *ab[4];
            int     arr[] = {4, 3, 2, 1, 5};

            init_ab_stacks_int_arr(ab, arr, 5);
            REQUIRE(num_len(ab[0]) == 5);
            push_swap(ab, false);
            REQUIRE(is_sorted(ab[0], CHECK_ALL, true, true));
        }
    }

    SECTION("Weird combinations [ranked method]") {

        SECTION("5 1 2 4 3") {
            t_num   *ab[4];
            int     arr[] = {3, 4, 2, 1, 5};

            init_ab_stacks_int_arr(ab, arr, 5);
            REQUIRE(num_len(ab[0]) == 5);
            push_swap(ab, false);
            REQUIRE(is_sorted(ab[0], CHECK_ALL, true, true));
        }

        SECTION("3 5 1 4 2") {
            t_num   *ab[4];
            int     arr[] = {2, 4, 1, 5, 3};

            init_ab_stacks_int_arr(ab, arr, 5);
            REQUIRE(num_len(ab[0]) == 5);
            push_swap(ab, false);
            REQUIRE(is_sorted(ab[0], CHECK_ALL, true, true));
        }

        SECTION("3 2 1 4 5") {
            t_num   *ab[4];
            int     arr[] = {5, 4, 1, 2, 3};

            init_ab_stacks_int_arr(ab, arr, 5);
            REQUIRE(num_len(ab[0]) == 5);
            push_swap(ab, false);
            REQUIRE(is_sorted(ab[0], CHECK_ALL, true, true));
        }

        SECTION("1 4 2 5 3") {
            t_num   *ab[4];
            int     arr[] = {3, 5, 2, 4, 1};

            init_ab_stacks_int_arr(ab, arr, 5);
            REQUIRE(num_len(ab[0]) == 5);
            push_swap(ab, false);
            REQUIRE(is_sorted(ab[0], CHECK_ALL, true, true));
        }
    }

    SECTION("3 numbers") {

        SECTION("All possible combinations") {
            t_num   *ab[4];
            int     n = 3;
            int     arr[n];
            int     temp;

            arr[0] = 3; arr[1] = 2; arr[2] = 1;
            for (int j = 1; j <= n; j++)
            {
                for (int i = 0; i < n-1; i++)
                {
                    temp = arr[i];
                    arr[i] = arr[i + 1];
                    arr[i + 1] = temp;
                    init_ab_stacks_int_arr(ab, arr, n);
                    REQUIRE(num_len(ab[0]) == n);
                    push_swap(ab, false);
                    REQUIRE(is_sorted(ab[0], CHECK_ALL, true, true));
                    REQUIRE(!ab[1]);
                    num_free_all(ab[0]);
                }
            }
        }
    }

    SECTION("5 numbers") {

        SECTION("All possible combinations") {
            t_num   *ab[4];
            int     n = 5;
            int     arr[n];
            int     temp;

            arr[0] = 5; arr[1] = 4; arr[2] = 3; arr[3] = 2; arr[4] = 1;
            for (int j = 1; j <= n; j++)
            {
                for (int i = 0; i < n-1; i++)
                {
                    temp = arr[i];
                    arr[i] = arr[i + 1];
                    arr[i + 1] = temp;
                    init_ab_stacks_int_arr(ab, arr, n);
                    REQUIRE(num_len(ab[0]) == n);
                    push_swap(ab, false);
                    REQUIRE(is_sorted(ab[0], CHECK_ALL, true, true));
                    REQUIRE(!ab[1]);
                    num_free_all(ab[0]);
                }
            }
        }
    }
}
