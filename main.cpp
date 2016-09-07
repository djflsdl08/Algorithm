#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode {
    element data;
    ListNode *link;
}ListNode;

void error(char *message){
    fprintf(stderr,"%s\n",message);
    exit(1);
}

ListNode* create_node(element data,ListNode *link){
    ListNode *new_node;
    new_node = (ListNode *)malloc(sizeof(ListNode));
    if(new_node==NULL) {
        error("memory allocation error");
        exit(1);
    }
    new_node -> link = link;
    new_node -> data = data;
    return (new_node);
}

void display(ListNode *head){
    ListNode *p;
    p = head;
    while(p!=NULL){
        printf("%d -> ",p->data);
        p = p->link;
    }
    printf("\n");
}

void insert_node(ListNode **phead,ListNode *p,ListNode *new_node){
    if(*phead == NULL){
        new_node -> link = NULL;
        *phead = new_node;
    }
    else if(p==NULL){
        new_node -> link = *phead;
        *phead = new_node;
    }
    else {
        new_node -> link = p -> link;
        p -> link = new_node;
    }
}

void remove_node(ListNode **phead,ListNode *p,ListNode *removed){
    if(p==NULL){
        *phead = (*phead) -> link;
    }
    else {
        p->link = removed -> link;
    }
    free(removed);
}

ListNode* concat(ListNode *head1,ListNode *head2){
    ListNode *p;
    if(head1 == NULL) return head2;
    else if(head2 == NULL) return head1;
    else {
        p = head1;
        while(p->link!=NULL){
            p = p->link;
        }
        p->link = head2;
        return head1;
    }
}

ListNode* reverse(ListNode *head){
    ListNode *p,*q,*r;
    p = head;
    q = NULL;
    while(p!=NULL){
        r = q;
        q = p;
        p = p->link;
        q ->link = r;
    }
    return q;
}

ListNode* search(ListNode *head,element data){
    ListNode *p = head;
    while(p!=NULL){
        if(p->data == data) return p;
        p = p->link;
    }
    return p;
}

void insert_first(ListNode **phead,ListNode *node){
    if(*phead == NULL){
        *phead = node;
        node -> link = node;
    }
    else {
        node -> link = (*phead) -> link;
        (*phead) -> link = node;
    }
}

void insert_last(ListNode **phead,ListNode *node){
    if(*phead == NULL){
        *phead = node;
        node -> link = node;
    }
    else {
        node -> link = (*phead) -> link;
        (*phead) -> link = node;
        (*phead) = node;
    }
}

void display_circular(ListNode *head){
    ListNode *p;
    if(head == NULL) return;
    p = head;
    do {
        printf("%d -> ",p->data);
        p = p->link;
    }while(p!=head);
    printf("\n");
}

void remove_first(ListNode **head){
    ListNode *p = (*head)->link;
    if(p==(*head)){
        *head =NULL;
    }
    else {
        (*head) -> link = p -> link;
    }
    free(p);
}

void remove_last(ListNode **head){
    ListNode *p = *head;
    if(p == p -> link){
        *head = NULL;
    }
    else {
        while(p->link!=*head){
            p = p -> link;
        }
        p -> link = (*head) -> link;
        *head = p;
    }
    free(p);
}
int main() {
    ListNode *list1=NULL,*list2=NULL,*list3=NULL;
    ListNode *p;

    //List1 = 30->20->10
    insert_node(&list1,NULL,create_node(10,NULL));
    insert_node(&list1,NULL,create_node(20,NULL));
    insert_node(&list1,NULL,create_node(30,NULL));
    display(list1);

    //List1 = 20->10
    remove_node(&list1,NULL,list1);
    display(list1);

    //List2 = 70 -> 60 -> 50
    insert_node(&list2,NULL,create_node(50,NULL));
    insert_node(&list2,NULL,create_node(60,NULL));
    insert_node(&list2,NULL,create_node(70,NULL));
    display(list2);

    //list1 = list1 + list2
    list1 = concat(list1,list2);
    display(list1);

    list1 = reverse(list1);
    display(list1);

    p = search(list1,20);
    printf("탐색성공:%d\n",p->data);

    //list3 : Circular Linked list
    insert_first(&list3,create_node(10,NULL));
    insert_first(&list3,create_node(20,NULL));
    insert_first(&list3,create_node(40,NULL));
    insert_last(&list3,create_node(30,NULL));
    insert_last(&list3,create_node(50,NULL));
    display_circular(list3);

    remove_first(&list3);
    display_circular(list3);
    remove_last(&list3);
    display_circular(list3);
 }