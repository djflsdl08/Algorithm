#include <stdio.h>
#include <stdlib.h>
#define MAX 50
#define TRUE 1
#define FALSE 0

int visited[MAX];
int visitedb[MAX];
int count;

typedef struct {
	int n;
	int max[MAX][MAX];
}GraphType;

typedef struct {
	int queue[MAX];
	int front,rear;
}QueueType;

void init_q(QueueType *q) {
	q->front=q->rear = 0;
}

int is_empty(QueueType *q) {
	return (q->front==q->rear);
}

int is_full(QueueType *q) {
	return ((q->rear+1)%MAX==q->front);
}

void enqueue(QueueType *q,int item) {
	if(is_full(q)) {
		return;
	}
	q->rear = (q->rear+1)%MAX;
	q->queue[q->rear] = item;
}

int dequeue(QueueType *q) {
	if(is_empty(q))
		exit(1);
	q->front = (q->front+1)%MAX;
	return q->queue[q->front];
}
void init(GraphType *g) {
	int row,col;

	g->n=0;
	for(row=0;row<MAX;row++) {
		for(col=0;col<MAX;col++) {
			g->max[row][col]=0;
		}
	}
}

void insert_vertex(GraphType *g,int v) {
	if((g->n)+1>MAX) {
		printf("그래프 개수 초과");
		return;
	}
	g->n++;
}

void insert_edge(GraphType *g,int start,int end) {
	if(start>=g->n||end>=g->n) {
		printf("그래프 정점 번호 오류");
		return;
	}
	g->max[start][end] = 1;
	g->max[end][start] = 1;
}

void delete_edge(GraphType *g,int start,int end) {
	if(start>=g->n||end>=g->n) {
		printf("그래프 정점 번호 오류");
		return;
	}
	g->max[start][end]=0;
	g->max[end][start]=0;
}

void print(GraphType *g) {
	int row,col;

	for(row=0;row<g->n;row++) {
		for(col=0;col<g->n;col++) {
			if(g->max[row][col])
				printf("(%d,%d)",row,col);
		}
		printf("\n");
	}
}

void dfs(GraphType *g,int v) {
	int w;
	visited[v] = TRUE;
	printf("%d ",v);
	for(w=0;w<g->n;w++) {
		if(g->max[v][w]&&!visited[w])
			dfs(g,w);
	}
}

void bfs(GraphType *g,int v) {
	int w;
	QueueType q;
	init_q(&q);
	visitedb[v] = TRUE;
	printf("%d ",v);
	enqueue(&q,v);
	while(!is_empty(&q)) {
		v = dequeue(&q);
		for(w=0;w<g->n;w++) {
			if(g->max[v][w]&&!visitedb[w]) {
				visitedb[w] = TRUE;
				printf("%d ",w);
				enqueue(&q,w);
			}
		}
	}
}

void find_connected_component(GraphType *g) {
	int i;

	count=0;
	for(i=0;i<g->n;i++) {
		if(!visited[i]) {
			count++;
			dfs(g,i);
		}
	}
}

int main() {
	int i;
	GraphType g;	//matrix

	init(&g);

	for(i=0;i<10;i++) {
		insert_vertex(&g,i);
	}

	insert_edge(&g,0,1);
	insert_edge(&g,1,2);
	insert_edge(&g,1,3);
	insert_edge(&g,2,4);
	insert_edge(&g,3,4);
	insert_edge(&g,3,5);
	insert_edge(&g,5,6);
	insert_edge(&g,5,7);
	insert_edge(&g,6,7);
	insert_edge(&g,7,8);
	insert_edge(&g,7,9);
	print(&g);
	printf("dfs : ");
	dfs(&g,6);
	printf("\nbfs : ");
	bfs(&g,6);
}