
/*
 * dslibs v0.1
 * stack example v0.1
 * weerdmonk Dec2014
 *
 */

#include <stack.h>

int main(void)
{
	Stack st = ds_stack_new(5);
        printf("stack occupancy = %d\n", st->top - st->sptr);
        ds_stack_push(st, 10);
        printf("stack occupancy = %d\n", st->top - st->sptr);
        ds_stack_push(st, 10);
        printf("stack occupancy = %d\n", st->top - st->sptr);
        ds_stack_push(st, 10);
        printf("stack occupancy = %d\n", st->top - st->sptr);
        ds_stack_push(st, 10);
        printf("stack occupancy = %d\n", st->top - st->sptr);
        ds_stack_push(st, 10);
        printf("stack occupancy = %d\n", st->top - st->sptr);
        ds_stack_push(st, 10);
        printf("stack occupancy = %d\n", st->top - st->sptr);
        printf("popped data = %d\n", (int)ds_stack_pop(st));
        printf("popped data = %d\n", (int)ds_stack_pop(st));
        printf("popped data = %d\n", (int)ds_stack_pop(st));
        printf("popped data = %d\n", (int)ds_stack_pop(st));
        printf("popped data = %d\n", (int)ds_stack_pop(st));
        printf("popped data = %d\n", (int)ds_stack_pop(st));

        return 0;
}

