#include "stdio.h"

// Data structures
typedef struct Stack {
	int* front;
	int backing[1024];
} Stack;

typedef struct Queue {
	int* front;
	int* back;
	int* end;
	int backing[1024];
} Queue;

typedef struct PQueue {
	int* front;
	int backing[1024];
} PQueue;

// Declarations
void Stack_push(Stack*, int);
int Stack_pop(Stack*);

void Queue_push(Queue*, int);
int Queue_pop(Queue*);

void PQueue_push(PQueue*, int);
int PQueue_pop(PQueue*);

// Implementations
void Stack_push(Stack* S, int x) {
	*(S->front) = x;
	S->front++;	
}

int Stack_pop(Stack* S) {
	S->front--;
	return *(S->front);
}

// So, it seems I implemented a ring buffer
// unecessarily
void Queue_push(Queue* Q, int x) {
	*(Q->front) = x;
	Q->front++;

	if (Q->front == Q->end)
		Q->front = Q->backing;
}

int Queue_pop(Queue* Q) {
	int ret = *(Q->back);	
	Q->back++;

	if (Q->back == Q->end)
		Q->back = Q->backing;

	return ret;
}

void PQueue_push(PQueue* Q, int x) {
	*(Q->front) = x;
	int* cur = Q->front++;

	// bubble up
	while (cur > Q->backing) {
		int* parent = Q->backing + (cur - Q->backing -1)/2;
		if (*cur <= *parent)
			break;

		int tmp = *parent;
		*parent = *cur;
		*cur = tmp;

		cur = parent;
	}
}

int PQueue_pop(PQueue* Q) {
	int ret = *(Q->backing);

	*(Q->backing) = *(--Q->front);

	int* cur = Q->backing;

	while (1) {
		int* lchild = Q->backing + 2*(cur-Q->backing)+1;
		int* rchild = lchild+1;

		if (lchild >= Q->front)
			break;

		if (rchild >= Q->front)
			rchild = lchild;

		int* maxchild = (*lchild > *rchild) ? lchild : rchild; 

		if (*maxchild < *cur) 
			break;

		int tmp = *maxchild;
		*maxchild = *cur;
		*cur = tmp;

		cur = maxchild;
	}

	return ret;
}

int test() {
	// init
	Stack S = {};
	S.front = S.backing;

	Queue Q = {};
	Q.front = Q.backing;
	Q.back = Q.backing;
	Q.end = Q.backing + 1024;

	PQueue P = {};
	P.front = P.backing;

	// run it
	int testing[] = {2, 1};
	for (int i=0; i<2; i++) {
		int x = testing[i];
		printf("%d\n", x);
		/*Stack_push(&S, x);*/
		Queue_push(&Q, x);
		/*PQueue_push(&P, x);*/
	}

	int* p = P.backing-1;
	while (++p < P.front)
		printf("%d,", *p);
	printf("\n");

	for (int i=0; i<2; i++) {
		int x = testing[i];
		printf("%d\n", Queue_pop(&Q));
	}

}

int submission() {
	int N;

	while ( scanf("%d", &N) >= 0 ) {
		char opts = 1 + (1<<1) + (1<<2);
		// init
		Stack S = {};
		S.front = S.backing;

		Queue Q = {};
		Q.front = Q.backing;
		Q.back = Q.backing;
		Q.end = Q.backing + 1024;

		PQueue P = {};
		P.front = P.backing;

		for (; N>0; N--) {
			int op; 
			int x;

			scanf("%d", &op);
			scanf("%d", &x);

			switch (op) {
				case 1:
					Stack_push(&S, x);
					Queue_push(&Q, x);
					PQueue_push(&P, x);
					break;
				case 2:
					if (opts & 1)
						if (Stack_pop(&S) != x)
							opts -= 1;

					if (opts & (1<<1))
						if (Queue_pop(&Q) != x)
							opts -= 1<<1;

					if (opts & (1<<2))
						if (PQueue_pop(&P) != x)
							opts -= 1<<2;
					break;
			}

		}

		if (!opts) {
			printf("impossible\n");
			continue;
		}

		if (opts & 1)
			if (opts-1)
				goto ambiguous;
			else {
				printf("stack\n");
				continue;
			}

		if (opts & (1<<1))
			if (opts-(1<<1))
				goto ambiguous;
			else {
				printf("queue\n");
				continue;
			}


		if (opts & (1<<2))
			if (opts-(1<<2))
				goto ambiguous;
			else {
				printf("priority queue\n");
				continue;
			}

ambiguous:
		printf("not sure\n");
		continue;
	}

	return 0;
}

int main() {
	submission();
	return 0;
}
