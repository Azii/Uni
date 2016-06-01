#include "RR.h"
#include "task.h"
#include <Queue.c>
#include <stdlib.h>

int tick;
Queue * queue;
task * running;

int init_RR(int time_step)
{
	tick = time_step;
	queue = queue_new(NULL);
}

void free_RR()
{
	queue_free(queue);
	free(running);
}

void arrive_RR(int id, int length)
{
	task * rr = malloc(sizeof(task));
	rr->id = id;
	rr->length = length;
	queue_offer(queue, rr);
}

void tick_RR()
{
	if (running != NULL)
	{
		running->length -= tick;
		if (running->length <= 0)
		{
			free(running);
		}else
		{
			queue_offer(queue, running);
		}
	}
	running = queue_offer(queue);
	switch_task(running->id);
}

void finish_RR(int id)
{
	tick_RR();
}
