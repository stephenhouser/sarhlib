

#undef stack_t

typedef struct {
		int top;
		int max_elements;
		void **contents;
} Stack;

void stack_init(Stack *stack, int max_elements);
void stack_destroy(Stack *stack);
int stack_empty(Stack *stack);
int stack_full(Stack *stack);
void stack_push(Stack *stack, void *element);
void *stack_pop(Stack *stack);

void stack_dump(Stack *stack, void (*dump_func)(void *));
