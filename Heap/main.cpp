//Priority Queue
/*
 * 정렬이 안 된 배열,리스트 => 삽입 : O(1), 삭제 : O(n)
 * 정렬이 된 배열,리스트 => 삽입 : O(n), 삭제 : O(1)
 * heap(히프) : 완전 이진 트리, 반 정렬 상태
 *            최대히프 => 가장 큰 값 : 루트노드(부모노드key >= 자식노드key)
 *            최소히프 => 가장 작은 값 : 루트노드(부모노드key <= 자식노드key)
 */

#include <stdio.h>
#define MAX_ELEMENT 200
typedef struct {
    int key;
}element;
typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
}HeapType;

void init(HeapType *head){
    head->heap_size=0;
}

void insert_max_heap(HeapType *heap,element x){
    int i;
    i = ++(heap->heap_size);

    while((i!=1)&&(x.key)>heap->heap[i/2].key){
        heap->heap[i] = heap->heap[i/2];
        i/=2;
    }
    heap->heap[i] = x;
}

element delete_max_heap(HeapType *heap){
    int parent,child;
    element item,temp;

    item = heap->heap[1];
    temp = heap->heap[(heap->heap_size)--];
    parent = 1;
    child = 2;
    while(child<=heap->heap_size){
        if(child < heap->heap_size && (heap->heap[child].key)<(heap->heap[child+1].key))
            child++;
        if(temp.key>=heap->heap[child].key) break;
        heap->heap[parent] = heap->heap[child];
        parent = child;
        child *=2;
    }
    heap->heap[parent] = temp;
    return item;
}

void print_heap(HeapType *heap){
    int size = heap->heap_size;
    while(size--){
        printf("%d\t",heap->heap[(heap->heap_size)-size].key);
    }
    printf("\n");
}

int main(){
    HeapType head;
    element e1={10},e2={5},e3={30};
    element e4,e5,e6;

    init(&head);
    insert_max_heap(&head,e1);
    insert_max_heap(&head,e2);
    insert_max_heap(&head,e3);
    print_heap(&head);

    e4 = delete_max_heap(&head);
    printf("< %d > ",e4.key);
    e5 = delete_max_heap(&head);
    printf("< %d > ",e5.key);
    e6 = delete_max_heap(&head);
    printf("< %d > ",e6.key);
}