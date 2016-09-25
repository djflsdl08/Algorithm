#include <stdio.h>
#include <stdlib.h>
#define MAX 200
#define m 10

typedef struct {
    int key;
}element;
typedef struct {
    element heap[MAX];
    int size;
}HeapType;

void init(HeapType *h){
    h->size = 0;
}

void insert_min_heap(HeapType *h,element x){
    int i;
    i = ++(h->size);

    while((i!=1)&&(x.key<h->heap[i/2].key)){
        h->heap[i] = h->heap[i/2];
        i /= 2;
    }
    h->heap[i] = x;
}

element delete_min_heap(HeapType *h){
    int parent,child;
    element item,temp;
    item = h->heap[1];
    temp = h->heap[(h->size)--];
    parent = 1;
    child = 2;

    while(child<=h->size){
        if((child<h->size)&&h->heap[child].key>h->heap[child+1].key)
            child ++;
        if(temp.key<=h->heap[child].key) break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

void sort_heap(element arr[],int num){
    int i;
    HeapType h;
    init(&h);
    for(i=0;i<num;i++){
        insert_min_heap(&h,arr[i]);
    }
    for(i=0;i<num;i++){
        arr[i] = delete_min_heap(&h);
    }
}

int main(){
    int a[m] = {5,7,3,2,8,9,10,6,4,1};
    element as[m];
    int i;

    printf("before sorting\n");
    for(i=0;i<m;i++){
        as[i].key = a[i];
        printf("%d ",as[i].key);
    }
    printf("\n");

    sort_heap(as,m);
    printf("after sorting\n");
    for(i=0;i<m;i++){
        printf("%d ",as[i].key);
    }
    printf("\n");

    printf("before sorting\n");
    for(i=0;i<m;i++){
        as[i].key = rand()/100;
        printf("%d ",as[i].key);
    }
    printf("\n");

    sort_heap(as,m);
    printf("after sorting\n");
    for(i=0;i<m;i++){
        printf("%d ",as[i].key);
    }
    printf("\n");
}