#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define KEY_SIZE 10
#define TABLE_SIZE 13
#define equal(e1,e2) (!strcmp(e1.key,e2.key))

typedef struct {
	char key[KEY_SIZE];
}element;

typedef struct ListNode {
	element item;
	struct ListNode *link;
}ListNode;

ListNode *hash_table[TABLE_SIZE];

void init_table(ListNode *ht[]) {
	int i;
	for(i=0;i<TABLE_SIZE;i++)
		ht[i]=NULL;
}

int transform(char *key) {
	int number=0;
	while(*key)
		number+=*key++;
	return number;
}

int hash_function(char *key) {
	return transform(key)%TABLE_SIZE;
}

void hash_chain_add(element item, ListNode *ht[]) {
	int hash_value=hash_function(item.key);

	ListNode *ptr;							// new node
	ListNode *node_before=NULL;				// before node
	ListNode *node=ht[hash_value];			// present node

	for( ; node ;node_before=node,node=node->link) {
		if(equal(node->item,item)){
			printf("key is already in the table\n");
			return;
		}
	}
	ptr=(ListNode *)malloc(sizeof(ListNode));	// memory allocation
	ptr->item=item;
	ptr->link=NULL;
	if(node_before)
		node_before->link=ptr;
	else
		ht[hash_value]=ptr;
}

void hash_chain_find(element item,ListNode *ht[]) {
	ListNode *node;
	int hash_value=hash_function(item.key);
	for(node=ht[hash_value];node;node=node->link){
		if(equal(node->item,item)){
			printf("key is found on index %d\n",hash_value);
			return;
		}
	}
	printf("the key is not found\n");
}

void hash_chain_delete(element item,ListNode *ht[]) {
	ListNode *node, *node_before=NULL;
	int hash_value = hash_function(item.key);;
	for(node=ht[hash_value];node;node_before=node,node=node->link) {
		if(equal(node->item,item)) {
			printf("key is delete on index %d\n",hash_value);
			if(node_before)
				node_before->link = node->link;
			else {
				if(node->link)
					ht[hash_value] = node->link;
				else
					ht[hash_value] = NULL;
			}
			free(node);
			return;
		}
	}
}

void hash_chain_print(ListNode *ht[]) {
	int i;
	ListNode *node;
	for(i=0;i< TABLE_SIZE;i++){
       printf("[%2d]", i);
		node=ht[i];
		while(node){
			printf(" %s ",node->item.key);
			node=node->link;
		}
		printf("\n");
	}
}
		
int main() {
	
    element tmp;
	// ListNode *ht=new ListNode*[TABLE_SIZE];
	init_table(hash_table);
	int op;
	while(1){
		printf("insert the operation you want(0:insert, 1:search, 2:delete, 3:finish) >> ");
		scanf("%d",&op);
		if(op==3) break;
		printf("insert a key >> ");

		scanf("%s",tmp.key);
		if(op==0)
			hash_chain_add(tmp,hash_table);
		else if(op==1)
			hash_chain_find(tmp,hash_table);
		else if(op==2)
			hash_chain_delete(tmp,hash_table);

		hash_chain_print(hash_table);
	}
}
