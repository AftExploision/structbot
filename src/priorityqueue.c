#include <string.h> //memcpy
#include <stdlib.h> //realloc
#include <math.h> //log, pow

#include "priorityqueue.h"
#include "structbot/interface.h"
#include "structbot/error.h"

//Takes in a priority queue and ensures it's a min-heap
static void heapify(structbot_priorityqueue *pq) {
	if (pq->mySize < 1) {
		return;
	}
	//Start at the root. Check the children. If needed, swap. If swap, go down that subtree
	size_t index = pq->mySize;
	structbot_event tmp = {};
	while (1) {
		//If our index has no children, return
		if (index*2 + 1 > pq->mySize - 1) {
			return;
		}
		//If the right doesn't exist, check for swap conditions with the left child. 
		//Return as the left child can also not have any children
		if (index*2 + 2 > pq->mySize - 1) {
			if (pq->data[index].priority > pq->data[index*2 + 1].priority) {
				memcpy(&tmp, &(pq->data[index]), sizeof(structbot_event));
				memcpy(&(pq->data[index]), &(pq->data[index*2 + 1]), sizeof(structbot_event));
				memcpy(&(pq->data[index*2 + 1]), &tmp, sizeof(structbot_event));
			}
			return;
		}
		//Find the smallest index and swap with it
		if (pq->data[index*2 + 1].priority < pq->data[index*2 + 2].priority && pq->data[index * 2 + 1].priority < pq->data[index].priority) {
			memcpy(&tmp, &(pq->data[index*2 + 1]), sizeof(structbot_event));
			memcpy(&(pq->data[index*2 + 1]), &(pq->data[index]), sizeof(structbot_event));
			memcpy(&(pq->data[index]), &tmp, sizeof(structbot_event));
			index = index*2 + 1;
			continue;
		} else if (pq->data[index*2 + 2].priority < pq->data[index].priority) {
			memcpy(&tmp, &(pq->data[index*2 + 2]), sizeof(structbot_event));
			memcpy(&(pq->data[index*2 + 2]), &(pq->data[index]), sizeof(structbot_event));
			memcpy(&(pq->data[index]), &tmp, sizeof(structbot_event));
			index = index*2 + 2;
			continue;
		} else {
			return;
		}
	}
}

structbot_event* priorityqueue_remove(structbot_priorityqueue *pq) {
	//Error if pq is empty
	if (pq->mySize == 0) {
		return NULL;
	}
	
	//Allocate a pointer to return
	structbot_event* retEvent = malloc(sizeof(structbot_event));
	
	//Copy the root event to the return pointer
	memcpy(retEvent, pq->data, sizeof(structbot_event));
	
	//Now re-order the min-heap
	//If we set the last child to the root so it isn't NULL then we can heapify
	memcpy(&(pq->data[0]), &(pq->data[pq->mySize-1]), sizeof(structbot_event));
	
	//Update the size actually being used
	pq->mySize--;
	
	//If we're using only 1/4 or less of the capacity then free some memory
	if (pq->mySize <= pq->capacity >> 2) {
		pq->capacity >>= 2;
		pq->data = realloc(pq->data, pq->capacity * sizeof(structbot_event));
	}
	
	//Now we make the priority queue ordered correctly again
	heapify(pq);
	
	//return the pointer
	return retEvent;
}

int priorityqueue_add(structbot_priorityqueue *pq, structbot_event* e) {
	//Ensure pq can hold the new event
	pq->mySize++;
	if (pq->mySize > pq->capacity) {
		if (pq->capacity << 1 < pq->capacity) {
			return STRUCTBOT_ERR_PQOUTOFMEM;
		}
		pq->capacity <<= 1;
		pq->data = realloc(pq->data, pq->capacity * sizeof(structbot_event));
		if (pq->data == NULL) {
			return STRUCTBOT_ERR_PQADDNOREALLOC;
		}
	}
	
	//Add the last event to the end
	memcpy(&(pq->data[pq->mySize - 1]), e, sizeof(structbot_event));
	//Now make sure pq has the heap property
	//While it's paremt is smaller than it, switch the two
	size_t our_node = pq->mySize-1;
	size_t parent_node = 0;
	while (pq->data[our_node].priority < pq->data[parent_node = our_node/2].priority) {
		structbot_event tmp = {};
		memcpy(&tmp, &(pq->data[our_node]), sizeof(structbot_event));
		memcpy(&(pq->data[our_node]), &(pq->data[parent_node]), sizeof(structbot_event));
		memcpy(&(pq->data[parent_node]), &tmp, sizeof(structbot_event));
		our_node = parent_node;
	}
	
	return 0;
}
