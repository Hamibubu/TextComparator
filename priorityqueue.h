#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

#include "datatypes.h"


struct PRIORITYQUEUESTR {
	TYPE *heap;
	int size;
	COMPAREFUNC comparefunc;
};

typedef struct PRIORITYQUEUESTR * PRIORITYQUEUE;

#define INITALHEAPSIZE 100

#define left(n) (2*n+1)
#define right(n) (2*n+2)
#define parent(n) ((n-1)/2)


void swap(TYPE *x,TYPE *y);


PRIORITYQUEUE priorityqueue_create(COMPAREFUNC comparefunc);
void priorityqueue_offer(PRIORITYQUEUE priorityqueue,TYPE data);
BOOL priorityqueue_is_empty(PRIORITYQUEUE priorityqueue);
TYPE priorityqueue_poll(PRIORITYQUEUE priorityqueue);
TYPE priorityqueue_peek(PRIORITYQUEUE priorityqueue);
void priorityqueue_destroy(PRIORITYQUEUE priorityqueue);



#endif /* PRIORITYQUEUE_H_ */
