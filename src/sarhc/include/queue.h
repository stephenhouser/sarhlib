
/****** QUEUE ******/

/* The queue contains only pointers to the elements, not the elements themselves */

typedef struct {
		int front;
		int count;
		int max_elements;
		void **contents;
} Queue;

Queue *queue_create(void);
void queue_init(Queue *queue, int max_elements);
void queue_destroy(Queue *queue);
int queue_empty(Queue *queue);
int queue_full(Queue *queue);
void queue_enter(Queue *queue, void *element);
void *queue_delete(Queue *queue);
