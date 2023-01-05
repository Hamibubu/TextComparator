
#include <stdlib.h>
#include "priorityqueue.h"

void swap(TYPE *x,TYPE *y)
{
	TYPE tmp = *x;
	*x = *y;
	*y = tmp;
}


PRIORITYQUEUE priorityqueue_create(COMPAREFUNC comparefunc)
{
	PRIORITYQUEUE new = malloc(sizeof(struct PRIORITYQUEUESTR));
	new->heap = malloc(INITALHEAPSIZE * sizeof(TYPE));
	int i;
	for(i=0;i<INITALHEAPSIZE;i++)
		new->heap[i] =NULL;
	new->size = 0;
	new->comparefunc = comparefunc;

	return(new);
}

void priorityqueue_offer(PRIORITYQUEUE priorityqueue,TYPE data)
{
	int current = priorityqueue->size;

	priorityqueue->heap[current] = data;

	priorityqueue->size++;

	while(current > 0)
	{
		if(priorityqueue->comparefunc(priorityqueue->heap[current],priorityqueue->heap[parent(current)]) < 0)
			swap(&(priorityqueue->heap[current]),&(priorityqueue->heap[parent(current)]));

		current = parent(current);
	}
}

BOOL priorityqueue_is_empty(PRIORITYQUEUE priorityqueue)
{
	return priorityqueue->size==0;
}

TYPE priorityqueue_poll(PRIORITYQUEUE priorityqueue)
{
	TYPE toret = priorityqueue->heap[0];
	int curr = 0;
	int min;

	if(priorityqueue->size > 0)
	{
		priorityqueue->size--;
		priorityqueue->heap[0] = priorityqueue->heap[priorityqueue->size];
		priorityqueue->heap[priorityqueue->size] = NULL;

		while(left(curr) < priorityqueue->size)	// Mientras tengamos al menos un hijo
		{
			min = left(curr);
			if(right(curr) < priorityqueue->size &&
			   priorityqueue->comparefunc(priorityqueue->heap[right(curr)],priorityqueue->heap[left(curr)])<0)
				min = right(curr);

			// min es el índice del hijo (izquierdo o derecho) que tiene el valor más
			// pequeño

			if(priorityqueue->comparefunc(priorityqueue->heap[curr],priorityqueue->heap[min]) > 0)
				swap(&(priorityqueue->heap[curr]),&(priorityqueue->heap[min]));
			else
				break;

			curr = min;
		}
	}
	return(toret);
}

TYPE priorityqueue_peek(PRIORITYQUEUE priorityqueue)
{
	TYPE toret = priorityqueue->heap[0];
	return(toret);
}

void priorityqueue_destroy(PRIORITYQUEUE priorityqueue)
{
	free(priorityqueue->heap);
	free(priorityqueue);
}

