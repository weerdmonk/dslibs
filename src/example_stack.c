
/*
 * dslibs v0.1
 * stack example v0.1
 * weerdmonk Dec2014
 *
 */

#include <stack.h>

int main(void)
{
	Stack st = ds_stack_new();
        printf("stack occupancy = %d\n", st->depth);
        ds_stack_push_val(st, 10);
        printf("stack occupancy = %d\n", st->depth);
        ds_stack_push_val(st, 20);
        printf("stack occupancy = %d\n", st->depth);
        ds_stack_push_val(st, 30);
        printf("stack occupancy = %d\n", st->depth);
        ds_stack_push_val(st, 40);
        printf("stack occupancy = %d\n", st->depth);
        ds_stack_push_val(st, 50);
        printf("stack occupancy = %d\n", st->depth);
        ds_stack_push_val(st, 60);
        printf("stack occupancy = %d\n", st->depth);
        printf("popped data = %u\n", ds_stack_pop_val(st));
        printf("popped data = %u\n", ds_stack_pop_val(st));
        printf("popped data = %u\n", ds_stack_pop_val(st));
        printf("popped data = %u\n", ds_stack_pop_val(st));
        printf("popped data = %u\n", ds_stack_pop_val(st));
        printf("popped data = %u\n", ds_stack_pop_val(st));
        printf("popped data = %u\n", ds_stack_pop_val(st));

        return 0;
}

