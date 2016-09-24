#include <stdio.h>
#include <string.h>
#define MAX 100

typedef struct {
    char key[20];
    int id;
}element;

typedef struct {
    element heap[MAX];
    int size;
}HeapType;

void init(HeapType *h){
    h->size = 0;
}

void insert_max_heap(HeapType *h,element x){
    int i;
    i = ++(h->size);

    while((i!=1)&&(strcmp(x.key,h->heap[i/2].key)>0)){
        h->heap[i] = h->heap[i/2];
        i/=2;
    }
    h->heap[i] = x;
}

element delete_max_heap(HeapType *h){
    int parent,child;
    element item,temp;

    item = h->heap[1];
    temp = h->heap[(h->size)--];
    parent = 1;
    child = 2;

    while(child<=h->size){
        if((child<h->size)&&strcmp(h->heap[child].key,h->heap[child+1].key)<0)
            child++;
        if(strcmp(temp.key,h->heap[child].key)>0) break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

void print(HeapType *h){
    int size = h->size;
    while(size--){
        printf("%s, %d\t",h->heap[(h->size)-size].key,h->heap[(h->size)-size].id);
    }
    printf("\n");
}

int main() {
    HeapType head;
    element e1 = {"egg", 1234}, e2 = {"structure", 321}, e3 = {"zoo", 2451};
    element e7 = {"love", 5624};
    element e4, e5, e6, e8;

    init(&head);
    insert_max_heap(&head, e1);
    print(&head);
    insert_max_heap(&head, e2);
    print(&head);
    insert_max_heap(&head, e3);
    print(&head);
    insert_max_heap(&head, e7);
    print(&head);

    printf("삭제 >> \n");
    e4 = delete_max_heap(&head);
    printf("%s, %d\n", e4.key, e4.id);
    e5 = delete_max_heap(&head);
    printf("%s, %d\n", e5.key, e5.id);
    e6 = delete_max_heap(&head);
    printf("%s, %d\n", e6.key, e6.id);
    e8 = delete_max_heap(&head);
    printf("%s, %d\n", e8.key, e8.id);
}