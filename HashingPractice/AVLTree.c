#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct avl_node {
    struct avl_node *left_child, *right_child;  
    char *data;
}avl_node;


int max(int x,int y)
{
	if(x>=y) return x;
	else return y;
}
// 왼쪽 회전 함수
avl_node *rotate_left( avl_node *parent)
{
    avl_node *child = parent->left_child;
	parent->left_child = child->right_child;
	child->right_child = parent;
	return child;
}
// 오른쪽 회전 함수
avl_node *rotate_right( avl_node *parent)
{
    avl_node *child = parent->right_child;
	parent->right_child = child->left_child;
	child->left_child = parent;
	return child;
}
// 오른쪽-왼쪽 회전 함수
avl_node *rotate_right_left( avl_node *parent)
{
    avl_node *child = parent->right_child;
	parent->right_child = rotate_left(child);
	return rotate_right(parent);
}
// 왼쪽-오른쪽 회전 함수
avl_node *rotate_left_right( avl_node *parent)
{
    avl_node *child = parent->left_child;
	parent->left_child = rotate_right(child);
	return rotate_left(parent);
}
// 트리의 높이를 반환
int get_height( avl_node *node)
{
	int height=0;
	if( node != NULL )
		height = 1 + max(get_height(node->left_child), 
						get_height(node->right_child));
	return height;
}

// 노드의 균형인수를 반환
int get_height_diff( avl_node *node) 
{
	if( node == NULL ) return 0;
	return get_height(node->left_child) - get_height(node->right_child);
} 

// 트리를 균형트리로 만든다
avl_node *rebalance(avl_node *node)
{
	int height_diff = get_height_diff(node);
	printf("*** Node : Left Sub Height - Right Sub Height = %d\n",height_diff);
	printf("* Node->left_child : Left Sub Height - Right Sub Height = %d\n",get_height_diff(node->left_child));
	printf("* Node->right_child : Left Sub Height - Right Sub Height = %d\n",get_height_diff(node->right_child));
	if( height_diff > 1 ){
		if( get_height_diff(node->left_child) > 0)
			node = rotate_left(node);
		else
			node = rotate_left_right(node);
	}
	else if ( height_diff < -1 ){
		if( get_height_diff((node)->right_child) < 0 )
			node = rotate_right(node);
		else
			node = rotate_right_left(node);
	}
	return node;
}

avl_node  *avl_add( avl_node *root, char *new_key)
{
	if(root!=NULL)
		printf("(%s %s)\n", root->data,new_key);
	else 
		printf("(root %s)\n", new_key);

	if( root == NULL ){
		root = (avl_node *)
		malloc(sizeof(struct avl_node));//new avl_node;
		if( root == NULL ){
			fprintf(stderr, "메모리 할당 에러\n");
			exit(1);
		}
		(root)->data = new_key;
		(root)->left_child = (root)->right_child = NULL;
	}
	else if (strcmp(new_key,(root)->data) < 0 ){  //new_key < (root)->data
 		(root)->left_child=avl_add(root->left_child, new_key);
		root = rebalance(root);
	}
	else if (strcmp(new_key,(root)->data) > 0 ){
		(root)->right_child=avl_add((root)->right_child, new_key);
		(root) = rebalance(root);
	}
	else {
		fprintf(stderr, "중복된 키 에러\n");
		exit(1);
	}
	return root;
}


// AVL 트리의 탐색함수
avl_node *avl_search( avl_node *node, char *key) 
{ 
	if( node == NULL ) return NULL; 
  //	printf("%d ", node->data);
	if( strcmp(key,node->data)==0) return node; 
	else if( strcmp(key,node->data) < 0) 
	   	return avl_search(node->left_child, key); 
	else 
		return avl_search(node->right_child, key); 
} 

void inorder( avl_node *node)
{
	if(node==NULL) return;
	inorder(node->left_child);
	printf("< %s >",node->data);
	inorder(node->right_child);
}

int main()
{
	//Dec, Jan, Apr, Mar, July, Aug, Oct, Feb, Sept, Nov, June, May
	avl_node *root=NULL;
	root=avl_add(root, "Dec");
	root=avl_add(root, "Jan");
	root=avl_add(root, "Apr");
	root=avl_add(root, "Mar");
	root=avl_add(root, "July");
	root=avl_add(root, "Aug");
	root=avl_add(root, "Oct");
	root=avl_add(root, "Feb");
	root=avl_add(root, "Sept");
	root=avl_add(root, "Nov");
	root=avl_add(root, "June");
	root=avl_add(root, "May");
	inorder(root);
	printf("\n");
	avl_node *node=avl_search(root, "May");
	
	if(node) printf("%s is found\n", node->data);
}