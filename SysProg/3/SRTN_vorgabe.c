#include "SRTN.h"
#include "task.h"
#include <stdlib.h>
#include <stdio.h>

Queue * queue;

//Hilfsfunktion, Nutzung optional, aber empfohlen
int length_comparator(const void *a, const void *b)
{
	return ((def_task*) a)->length - ((def_task*) b)->length;
}

static int srtn_isRunning;

int init_SRTN()
{
	queue = queue_new(NULL);
}

void free_SRTN()
{
	queue_free(queue);
}

void arrive_SRTN(int id, int length)
{	
	task * task = malloc(sizeof(task));
	task->id = id;
	task->length = length;
	
	queue_offer(task);
}

void tick_SRTN()
{
	//macht nichts :>
}

void finish_SRTN(int id)
{
	Queue * next = queue;
	Queue * smallest_length = next;
	while(1)
	{
		if (id == to_task_ptr(next)->id)
			queue_poll(next);
		else if (to_task_ptr(next)->length < to_task_ptr(smallest_length)->length)
			smallest_length = next;
		if (next->prev == NULL)
			break;
		next = next->prev;
	}
	
	switch_task(to_task_ptr(smallest_length)->id);
	return;
	
	for (int i = 0; i < 100; i++)
	{
		if (tasks[i]->id == id)
			free(tasks[i]);
	}
	task * task = tasks[0];
	
	for (int i = 0; i < 100; i++)
	{
		if (tasks[i]->length < task->length)
			task = tasks[i];
	}
	switch_task(task->id);
}

task * to_task_ptr(Queue * queue)
{
	return ((task*)(next->value));
}
