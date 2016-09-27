#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200

typedef struct {
    int key;
}element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
}HeapType;

void init(HeapType *h){
    h->heap_size = 0;
}

void insert_max_heap(HeapType *h,element item,int k){
    int i;
    i=++(h->heap_size);

    while((i!=1)&&(item.key>h->heap[(i+k-2)/k].key)){
        h->heap[i]=h->heap[(i+k-2)/k];
        i = (i+k-2)/k;
    }
    h->heap[i]=item;
}

int max(element heap[],int start,int number){
    int maxIndex = start;

    for(int i=start;i<start+number;i++){
        if(heap[maxIndex].key<=heap[i].key)
            maxIndex = i;
    }
    return maxIndex;
}

element delete_max_heap(HeapType *h,int k){
    int parent,child,num,cnt,max;
    element item,temp;

    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent = 1;
    child = 2;
    while(child<=h->heap_size){
        //if(child<h->heap_size&&h->heap[child].key<h->heap[child+1].key)
          //  child++;
        if(child<h->heap_size){
            cnt = 0;
            if(h->heap_size-child>=k-1)
                num = k;
            else num = h->heap_size - child + 1;
            max = h->heap[child].key;
            while(num--){
                if(max<h->heap[child+num].key) {
                    max = h->heap[child + num].key;
                    cnt = num;
                }
            }
            child+=cnt;
        }
        if(temp.key>=h->heap[child].key) break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child = child*k-(k-2);
    }
    h->heap[parent] = temp;
    return item;
}


void print_heap(HeapType *h){
    for(int i=1;i<=h->heap_size;i++){
        printf("< %d > ",h->heap[i].key);
    }
    printf("\n");
}

void heap_sort(element a[],int n,int k){
    int i;
    element arr[10]={0};
    HeapType h;

    init(&h);
    printf("insert_max_heap 함수 호출 >> (%d진트리)\n",k);
    for(i=0;i<n;i++){
        insert_max_heap(&h,a[i],k);
    }
    print_heap(&h);
    printf("delete_max_heap 함수 호출 >> (%d진트리)\n",k);
    for(i=n-1;i>=0;i--){
        arr[i] = delete_max_heap(&h,k);
        printf("%d ",arr[i]);
    }
    printf("\n");
}

int main() {
    element e[10] = {10, 2, 7, 9, 3, 40, 26, 15, 33, 28};
    HeapType heap2,heap3,heap4;

    init(&heap2);
    printf("2진트리\n");
    heap_sort(e,10,2);

    init(&heap3);
    printf("\n3진트리\n");
    heap_sort(e,10,3);

    init(&heap4);
    printf("\n4진트리\n");
    heap_sort(e,10,4);

    init(&heap4);
    printf("\n5진트리\n");
    heap_sort(e,10,5);

    init(&heap4);
    printf("\n6진트리\n");
    heap_sort(e,10,6);

    init(&heap4);
    printf("\n7진트리\n");
    heap_sort(e,10,7);

    printf("\nindex 0부터 10개일 때, 가장 key가 큰 원소의 index는 %d 이다.\n",max(e,0,10));
    printf("index 6부터 4개일 때, 가장 key가 큰 원소의 index는 %d 이다.\n",max(e,6,4));
    printf("index 3부터 5개일 때, 가장 key가 큰 원소의 index는 %d 이다.\n",max(e,3,5));
}