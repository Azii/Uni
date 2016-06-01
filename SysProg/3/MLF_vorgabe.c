#include "MLF.h"
#include "task.h"
#include <stdlib.h>
#include <stdio.h>
// Vorgabe nicht lauffähig, eine Queue muss selbst geschrieben und implementiert werden.
Queue **q;

//Hilfsvarablen, Nutzung optional aber empfohlen.
static int *step;
static int num;
static int used;
static def_task *task;
static Queue *task_queue;
static int task_queue_idx;

// Hilfsfunktionen, an denen sich orientiert werden kann. Sie können auch genutzt werden.

int smallestReadyQueue()
{
	int i;
	for (i = 0; i < num; i++)
	{
		if (queue_size(*(q + i)) > 0)
		{
			return i;	
		} 
	}
	return -1;
}

void schedule_task()
{
	task_queue_idx = smallestReadyQueue();

	if (task_queue_idx != -1)
	{
		task_queue = *(q + task_queue_idx);
		task = (def_task*) queue_peek(task_queue);
		switch_task(task->id);
	}
	else
	{
		switch_task(IDLE);
		task = NULL;
		task_queue = NULL;
	}
	used = 0;	
}
// Ende Hilfsfunktionen


int init_MLF(int time_step, int num_queues)
{
	q = malloc(sizeof(q**) * num_queues);
	num = num_queues;
	step = time_step;
}

void free_MLF()
{
	for(int i = 0; i < num; i++)
	{
		queue_free(q[i]);
	}
}

void arrive_MLF(int id, int length)
{
	task * task = malloc(sizeof(task));
	task->id = id;
	task->length = length;
	queue_offer(q[0], task);
}

void tick_MLF()
{
	int smallest_ready = smallestReadyQueue();
	Queue * next = queue_poll(q[smallest_ready]);
	if (smallest_ready < num)
		smallest_ready++;
	queue_offer(q[smallest_ready]);
	switch_task(((task*)(next->value))->id);
}

void finish_MLF(int id)
{
	for (int i = smallestReadyQueue(); i < smallestReadyQueue() + 2; i++)
	{
		// nach dem task mit der id suchen, löschen, dann neuen
	}
	tick_MLF();
}
