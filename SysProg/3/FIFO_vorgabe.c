#include "FIFO.h"
#include "task.h"
#include <stdlib.h>
#include <stdio.h>

static Queue *q;


int init_FIFO()
{
	q = queue_new(NULL);
}

void free_FIFO()
{
	queue_free(q);
}

void arrive_FIFO(int id, int length)
{
	task * task = malloc(sizeof(task));
	task->id = id;
	task->length = length;
	queue_offer(q, task);
}

void tick_FIFO()
{
	// macht nichts :>
}

void finish_FIFO(int id)
{
	switch_task(((task*)(queue_poll(q)->value))->id);
}