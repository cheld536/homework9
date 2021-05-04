/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			printf("메모리 해제가 끝났습니다. 프로그램을 종료합니다. \n");
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)			// 중위순회
{
	if(ptr)
	{
		inorderTraversal(ptr->left);		// 왼쪽에 있는 노드 부터 먼저 들어간다.
		printf("[%d] ",ptr->key);				// 중간에 있는 노드 부터 출력
		inorderTraversal(ptr->right);		// 오른쪽에 있는 노드 탐색
	}
}

void preorderTraversal(Node* ptr)			// 전위순회
{
	if(ptr)
	{
		printf("[%d] ",ptr->key);				// NULL이 아니라면 맨 처음 노드를 출력 부모노드 탐색후 자식 노드 탐색
		preorderTraversal(ptr->left);		// 왼쪽부터 탐색
		preorderTraversal(ptr->right);		// 오른쪽 탐색
	}
}

void postorderTraversal(Node* ptr)			// 후위순회
{
	preorderTraversal(ptr->left);			// 왼쪽 탐색
	preorderTraversal(ptr->right);			// 오른쪽 탐색
	printf("[%d] ",ptr->key);					// 자식 노드 탐색 후 부모 노드 탐색
}


int insert(Node* head, int key)
{
	Node* new = (Node*)malloc(sizeof(Node)); // 사용자로부터 새로 입력 받을 노드를 동적할당해준다. 

	new->key = key;							 // 노드를 입력받은 키값으로 초기화 해준다		
	new->left = NULL;						 // 노드의 왼쪽 루트 가르키는 값을 널로 초기화
	new->right = NULL;						 // 노드의 오른쪽 루트가 가르키는 값을 널로 초기화	
	Node *findnode = head ->left;  			// 트리를 탐색할 노드를 선언하고 루트의 주소값을 저장한다.

	if(head->left == NULL)					// 루트가 비었으면 new노드를 루트로 삽입한다.
	{
		head->left = new;
	}	
										// 만약 루트노드가 있다면 
	while (findnode != NULL)			// NULL이 아닐때 까지 반복
	{
		if(findnode->key < key)				// 입력값이 더 클때
		{
			if(findnode->right == NULL)		// 노드의 오른쪽이 비었으면 
			{
				findnode->right = new;		// 오른쪽에 입력한 노드를 위치 시킨다.
				break;						
			}
			findnode= findnode->right;		// 오른쪽이 차있으면 다음 노드로 넘어간다.
		}
		else								// 부모노드보다 작거나 같으면 
		{
			if(findnode->left == NULL)		// 왼쪽이 널이면 
			{
				findnode->left = new;		// 왼쪽에 입력한 노드를 위치 시킨다.
				break;
			}
			findnode = findnode->left;		// 널이 아니면 왼쪽노드를 탐색한다.
		}
	}
	

	

}

int deleteLeafNode(Node* head, int key)
{
	Node* target = head->left;
	Node* parents = NULL;
	Node* remove = NULL;
	while (target != NULL)
	{
		
		if(key == target->key)
			break;
		if(key < target->key)
		{
			parents = target;
			target = target->left;
		}
		else if ( key > target->key)
		{
			parents = target;
			target = target->right;
		}
	}
	
	remove = target;
	if(target==NULL)
	{
		printf("삭제하려는 %d 노드가 없습니다.\n",key);
		return 0;
	} 
	if(target->left != NULL && target->right != NULL)
	{
		printf("삭제하려는 %d 노드는 리프노드가 아닙니다.\n");
		return 0;
	}

	if(target->left == NULL && target->right == NULL)				//자식이 없는 단일 노드 일때
	{
		if(target->key == parents->left->key)
		{
			free(remove);
			parents->left = NULL;
		}
		else if(target->key == parents->right->key)
		{
			free(remove);
			parents->right = NULL;
		}	
	}
	
return 0;

}

Node* searchRecursive(Node* ptr, int key)           // 재귀함수로 이진탐색을 진행한다.
{
	if(!ptr) return NULL;							
	if(key== ptr->key) return ptr;					// 찾고 있는 key값을 가진 노드의 주소를 반환
	if(key<ptr->key)								// 입력된 key값보다 탐색된 key값이 더 크면
		return searchRecursive(ptr->left,key);		// 왼쪽으로 이동한다.
	return searchRecursive(ptr->right,key);			// 아니면 오른쪽으로 이동
}

Node* searchIterative(Node* head, int key) 			// 반복적 탐색
{
	while(head)										// 헤드가 널이 아닐때까지 반복
	{
		if(key == head->key ) return head;			// key값을 찾으면 찾은 노드의 주소를 반환
		if(key < head->key)							// 입력된 key값보다 탐색된 key값이 더 크면
		{
			head = head->left;						// 왼쪽으로 이동
		}
		else										// 아니면 오른쪽으로 이동 
		{
			head=head->right;
		}
	}
	return NULL;
}


int freeBST(Node* head)
{
	if(head != NULL)					// 후위순회 탐색을 이용하여 자식 노드를 먼저 메모리 해제하고 부모노드를 해제한다.
	{
		freeBST(head->left);			
		if (head->right != head)		// 루트 노드까지만 탐색한다.
		{
			freeBST(head->right);
		}
		free(head);						// 메모리를 해제 해준다.
	}
	
}





