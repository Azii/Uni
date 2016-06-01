#include <stdlib.h>

struct Queue {
	struct Queue * prev;
	void* value;
};

typedef struct Queue Queue;

Queue* queue_new(int (*comparator)(const void *a, const void *b));
void queue_free(Queue *queue);
void* queue_offer(Queue *queue, void* value);
void* queue_peek(Queue *queue);
void* queue_poll(Queue *queue);
int queue_size(Queue *queue);

Queue* queue_new(int (*comparator)(const void *a, const void *b))
{
	Queue * q = malloc(sizeof(Queue));
	q->value = &comparator;
	return q;
}

void queue_free(Queue *queue)
{
	Queue * next = queue;
	Queue * temp = malloc(sizeof(Queue));
	while(next != NULL)
	{
		temp = next;
		next = next->prev;
		free(temp);
	}
}

void* queue_offer(Queue *queue, void* value)
{
	Queue * q = malloc(sizeof(Queue));
	q->value = value;
	Queue * next = malloc(sizeof(Queue));
	next = queue;
	while(1)
	{
		if (next->prev != NULL)
		{
			next = next->prev;
		}else
			break;
	}
	next->prev = q;
	return 0;
}

void* queue_peek(Queue *queue)
{
	return queue->value;
}

void* queue_poll(Queue *queue)
{
	void * ret_val = queue->value;
	Queue * temp = queue;
	queue = queue->prev;
	free(temp);
	return ret_val;
}

int queue_size(Queue *queue)
{
	int counter = 0;
	Queue * next = malloc(sizeof(Queue));
	next = queue;
	while(1)
	{
		if (next != NULL)
		{
			counter++;
			next = next->prev;
		}	
	}
}

