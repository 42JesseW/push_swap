#include "catch.hpp"
#include <random>

extern "C" {
	#include <push_swap.h>
}

bool	valid_stack_ptrs(t_num *stack)
{
	t_num	*num;
	t_num	*last;
	int		count;

	if (!stack)
		return (true);
	num = stack;
	count = 0;
	while (num)
	{
		if (!num->next)
			last = num;
		num = num->next;
		count++;
	}
	num = last;
	while (num)
	{
		num = num->prev;
		count--;
	}
	return (count == 0);
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

static void	init_ab_stacks(t_num **ab, int size)
{
	std::random_device			randomSeed;
	std::default_random_engine	random(randomSeed());
	t_num						*num;

	ab[0] = ab[1] = ab[2] = ab[3] = nullptr;
	for (int i=0; i < size; i++)
	{
		num = num_new(static_cast<int>((random() % (INT_MAX - 1) + 1)));
		num_add_front(ab, num);
		if (i == 0)
			ab[2] = num;
	}
}

TEST_CASE("ins_exec") {

	SECTION("unknown operation") {
		t_num *ab[4];
		t_num *first;
		t_num *last;
		int len;

		init_ab_stacks(ab, 10);
		first = ab[0];
		last = ab[2];

		len = num_len(ab[0]);
		ins_exec("lo", ab, false);
		REQUIRE(ab[0] == first);
		REQUIRE(ab[2] == last);
		REQUIRE(num_len(ab[0]) == len);
	}
}

TEST_CASE("ins_push") {

	SECTION("push from empty stack") {
		t_num	*ab[4];

		ab[0] = NULL;
		ab[1] = NULL;
		ins_exec(PUSHA, ab, false);
		REQUIRE(ab[0] == NULL);
		REQUIRE(ab[1] == NULL);
		ins_exec(PUSHB, ab, false);
		REQUIRE(ab[0] == NULL);
		REQUIRE(ab[1] == NULL);
	}

	SECTION("push to empty stack") {
		t_num	*ab[4];
		t_num	*first;
		int		size;

		size = 1;
		init_ab_stacks(ab, size);
		first = ab[0];
		ins_exec(PUSHB, ab, false);
		REQUIRE(num_len(ab[0]) == 0);
		REQUIRE(num_len(ab[1]) == 1);
		REQUIRE(first == ab[1]);
		ins_exec(PUSHA, ab, false);
		REQUIRE(num_len(ab[0]) == 1);
		REQUIRE(num_len(ab[1]) == 0);
		REQUIRE(first == ab[0]);
	}

	SECTION("push to stack with multiple items on it") {
		t_num	*ab[4];
		t_num	*first;
		int		size;

		size = 6;
		init_ab_stacks(ab, size);
		first = ab[0];
		ins_exec(PUSHB, ab, false);
		ins_exec(PUSHB, ab, false);
		ins_exec(PUSHB, ab, false);
		REQUIRE(first == ab[1]->next->next);
		REQUIRE(first->prev == ab[1]->next);
		REQUIRE(first->prev->prev == ab[1]);
		REQUIRE(num_len(ab[1]) == 3);
		REQUIRE(valid_stack_ptrs(ab[1]));
		ins_exec(PUSHA, ab, false);
		ins_exec(PUSHA, ab, false);
		ins_exec(PUSHA, ab, false);
		REQUIRE(first == ab[0]);
		REQUIRE(first->next == ab[2]->prev->prev->prev->prev);
		REQUIRE(valid_stack_ptrs(ab[0]));
	}
}

TEST_CASE("ins_rotate") {

	SECTION("rotate empty stack") {
		t_num	*ab[4];

		ab[0] = NULL;
		ab[1] = NULL;
		ins_exec(ROTATEA, ab, false);
		REQUIRE(ab[0] == NULL);
		REQUIRE(ab[1] == NULL);
		ins_exec(ROTATEB, ab, false);
		REQUIRE(ab[0] == NULL);
		REQUIRE(ab[1] == NULL);
	}

	SECTION ("rotate stack with one item") {
		t_num	*ab[4];
		t_num	*first;
		int		size;

		size = 1;
		init_ab_stacks(ab, size);
		first = ab[0];
		ins_exec(ROTATEA, ab, false);
		REQUIRE(first == ab[0]);
		ins_exec(PUSHB, ab, false);
		ins_exec(ROTATEB, ab, false);
		REQUIRE(first == ab[1]);
	}

	SECTION("rotate stack with two items") {
		t_num	*ab[4];
		t_num	*first;
		int		size;

		size = 2;
		init_ab_stacks(ab, size);
		first = ab[0];
		ins_exec(ROTATEA, ab, false);
		REQUIRE(first == ab[0]->next);
		REQUIRE(first->prev == ab[0]);
		REQUIRE(first == ab[2]);
		REQUIRE(valid_stack_ptrs(ab[0]));
		ins_exec(PUSHB, ab, false);
		ins_exec(PUSHB, ab, false);
		ins_exec(ROTATEB, ab, false);
		REQUIRE(first == ab[1]->next);
		REQUIRE(first->prev == ab[1]);
		REQUIRE(first == ab[3]);
		REQUIRE(valid_stack_ptrs(ab[1]));
	}

	SECTION("rotate stack with multiple items") {
		t_num	*ab[4];
		t_num	*first;
		t_num	*last;
		int		size;

		size = 4;
		init_ab_stacks(ab, size);
		first = ab[0];
		last = ab[2];
		ins_exec(ROTATEA, ab, false);
		REQUIRE(first == ab[2]);
		REQUIRE(first->prev == last);
		REQUIRE(valid_stack_ptrs(ab[0]));
		for (int i=0; i < size; i++)
			ins_exec(PUSHB, ab, false);
		last = ab[3];
		ins_exec(ROTATEB, ab, false);
		REQUIRE(first == ab[3]);
		REQUIRE(first->prev == last);
		REQUIRE(valid_stack_ptrs(ab[1]));
	}
}

TEST_CASE("ins_rrotate") {

	SECTION("reverse rotate empty stack") {
		t_num	*ab[4];

		ab[0] = NULL;
		ab[1] = NULL;
		ins_exec(REVERSE_ROTATEA, ab, false);
		REQUIRE(ab[0] == NULL);
		REQUIRE(ab[1] == NULL);
		ins_exec(REVERSE_ROTATEB, ab, false);
		REQUIRE(ab[0] == NULL);
		REQUIRE(ab[1] == NULL);
	}

	SECTION("reverse rotate stack with one item") {
		t_num	*ab[4];
		t_num	*first;
		int		size;

		size = 1;
		init_ab_stacks(ab, size);
		first = ab[0];
		ins_exec(REVERSE_ROTATEA, ab, false);
		REQUIRE(first == ab[0]);
		ins_exec(PUSHB, ab, false);
		ins_exec(REVERSE_ROTATEB, ab, false);
		REQUIRE(first == ab[1]);
	}

	SECTION("reverse rotate stack with two items") {
		t_num	*ab[4];
		t_num	*first;
		int		size;

		size = 2;
		init_ab_stacks(ab, size);
		first = ab[0];
		ins_exec(REVERSE_ROTATEA, ab, false);
		REQUIRE(first == ab[0]->next);
		REQUIRE(first->prev == ab[0]);
		REQUIRE(first == ab[2]);
		REQUIRE(valid_stack_ptrs(ab[0]));
		ins_exec(PUSHB, ab, false);
		ins_exec(PUSHB, ab, false);
		ins_exec(REVERSE_ROTATEB, ab, false);
		REQUIRE(first == ab[1]->next);
		REQUIRE(first->prev == ab[1]);
		REQUIRE(first == ab[3]);
		REQUIRE(valid_stack_ptrs(ab[1]));
	}

	SECTION("reverse rotate stack with multiple items") {
		t_num	*ab[4];
		t_num	*first;
		t_num	*last;
		int		size;

		size = 4;
		init_ab_stacks(ab, size);
		first = ab[0];
		last = ab[2];
		ins_exec(REVERSE_ROTATEA, ab, false);
		REQUIRE(first == ab[0]->next);
		REQUIRE(last == ab[0]);
		REQUIRE(valid_stack_ptrs(ab[0]));
		for (int i = 0; i < size; i++)
			ins_exec(PUSHB, ab, false);
		last = ab[3];
		ins_exec(REVERSE_ROTATEB, ab, false);
		REQUIRE(first == ab[3]);
		REQUIRE(last == ab[1]);
		REQUIRE(valid_stack_ptrs(ab[1]));
	}

}

TEST_CASE("ins_swap") {

	SECTION("swap empty stack") {
		t_num	*ab[4];

		ab[0] = NULL;
		ab[1] = NULL;
		ins_exec(SWAPA, ab, false);
		REQUIRE(ab[0] == NULL);
		REQUIRE(ab[1] == NULL);
		ins_exec(SWAPB, ab, false);
		REQUIRE(ab[0] == NULL);
		REQUIRE(ab[1] == NULL);
	}

	SECTION("swap stack with one item") {
		t_num	*ab[4];
		t_num	*first;
		int		size;

		size = 1;
		init_ab_stacks(ab, size);
		first = ab[0];
		ins_exec(SWAPA, ab, false);
		REQUIRE(first == ab[0]);
		ins_exec(PUSHB, ab, false);
		ins_exec(SWAPB, ab, false);
		REQUIRE(first == ab[1]);
	}

	SECTION("swap stack with two items") {
		t_num	*ab[4];
		t_num	*first;
		int		size;

		size = 2;
		init_ab_stacks(ab, size);
		first = ab[0];
		ins_exec(SWAPA, ab, false);
		REQUIRE(first == ab[0]->next);
		REQUIRE(first->prev == ab[0]);
		REQUIRE(first == ab[2]);
		REQUIRE(valid_stack_ptrs(ab[0]));
		ins_exec(PUSHB, ab, false);
		ins_exec(PUSHB, ab, false);
		ins_exec(SWAPB, ab, false);
		REQUIRE(first == ab[1]->next);
		REQUIRE(first->prev == ab[1]);
		REQUIRE(first == ab[3]);
		REQUIRE(valid_stack_ptrs(ab[1]));
	}

	SECTION("swap stack with multiple items") {
		t_num	*ab[4];
		t_num	*first;
		t_num	*second;
		int		size;

		size = 4;
		init_ab_stacks(ab, size);
		first = ab[0];
		second = first->next;
		ins_exec(SWAPA, ab, false);
		REQUIRE(first == ab[0]->next);
		REQUIRE(second == ab[0]);
		REQUIRE(valid_stack_ptrs(ab[0]));
		for (int i = 0; i < size; i++)
			ins_exec(PUSHB, ab, false);
		second = ab[1]->next;
		ins_exec(SWAPB, ab, false);
		REQUIRE(first == ab[3]->prev);
		REQUIRE(second == ab[1]);
		REQUIRE(valid_stack_ptrs(ab[1]));
	}

}
