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
			printf("�޸� ������ �������ϴ�. ���α׷��� �����մϴ�. \n");
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



void inorderTraversal(Node* ptr)			// ������ȸ
{
	if(ptr)
	{
		inorderTraversal(ptr->left);		// ���ʿ� �ִ� ��� ���� ���� ����.
		printf("[%d] ",ptr->key);				// �߰��� �ִ� ��� ���� ���
		inorderTraversal(ptr->right);		// �����ʿ� �ִ� ��� Ž��
	}
}

void preorderTraversal(Node* ptr)			// ������ȸ
{
	if(ptr)
	{
		printf("[%d] ",ptr->key);				// NULL�� �ƴ϶�� �� ó�� ��带 ��� �θ��� Ž���� �ڽ� ��� Ž��
		preorderTraversal(ptr->left);		// ���ʺ��� Ž��
		preorderTraversal(ptr->right);		// ������ Ž��
	}
}

void postorderTraversal(Node* ptr)			// ������ȸ
{
	preorderTraversal(ptr->left);			// ���� Ž��
	preorderTraversal(ptr->right);			// ������ Ž��
	printf("[%d] ",ptr->key);					// �ڽ� ��� Ž�� �� �θ� ��� Ž��
}


int insert(Node* head, int key)
{
	Node* new = (Node*)malloc(sizeof(Node)); // ����ڷκ��� ���� �Է� ���� ��带 �����Ҵ����ش�. 

	new->key = key;							 // ��带 �Է¹��� Ű������ �ʱ�ȭ ���ش�		
	new->left = NULL;						 // ����� ���� ��Ʈ ����Ű�� ���� �η� �ʱ�ȭ
	new->right = NULL;						 // ����� ������ ��Ʈ�� ����Ű�� ���� �η� �ʱ�ȭ	
	Node *findnode = head ->left;  			// Ʈ���� Ž���� ��带 �����ϰ� ��Ʈ�� �ּҰ��� �����Ѵ�.

	if(head->left == NULL)					// ��Ʈ�� ������� new��带 ��Ʈ�� �����Ѵ�.
	{
		head->left = new;
	}	
										// ���� ��Ʈ��尡 �ִٸ� 
	while (findnode != NULL)			// NULL�� �ƴҶ� ���� �ݺ�
	{
		if(findnode->key < key)				// �Է°��� �� Ŭ��
		{
			if(findnode->right == NULL)		// ����� �������� ������� 
			{
				findnode->right = new;		// �����ʿ� �Է��� ��带 ��ġ ��Ų��.
				break;						
			}
			findnode= findnode->right;		// �������� �������� ���� ���� �Ѿ��.
		}
		else								// �θ��庸�� �۰ų� ������ 
		{
			if(findnode->left == NULL)		// ������ ���̸� 
			{
				findnode->left = new;		// ���ʿ� �Է��� ��带 ��ġ ��Ų��.
				break;
			}
			findnode = findnode->left;		// ���� �ƴϸ� ���ʳ�带 Ž���Ѵ�.
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
		printf("�����Ϸ��� %d ��尡 �����ϴ�.\n",key);
		return 0;
	} 
	if(target->left != NULL && target->right != NULL)
	{
		printf("�����Ϸ��� %d ���� ������尡 �ƴմϴ�.\n");
		return 0;
	}

	if(target->left == NULL && target->right == NULL)				//�ڽ��� ���� ���� ��� �϶�
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

Node* searchRecursive(Node* ptr, int key)           // ����Լ��� ����Ž���� �����Ѵ�.
{
	if(!ptr) return NULL;							
	if(key== ptr->key) return ptr;					// ã�� �ִ� key���� ���� ����� �ּҸ� ��ȯ
	if(key<ptr->key)								// �Էµ� key������ Ž���� key���� �� ũ��
		return searchRecursive(ptr->left,key);		// �������� �̵��Ѵ�.
	return searchRecursive(ptr->right,key);			// �ƴϸ� ���������� �̵�
}

Node* searchIterative(Node* head, int key) 			// �ݺ��� Ž��
{
	while(head)										// ��尡 ���� �ƴҶ����� �ݺ�
	{
		if(key == head->key ) return head;			// key���� ã���� ã�� ����� �ּҸ� ��ȯ
		if(key < head->key)							// �Էµ� key������ Ž���� key���� �� ũ��
		{
			head = head->left;						// �������� �̵�
		}
		else										// �ƴϸ� ���������� �̵� 
		{
			head=head->right;
		}
	}
	return NULL;
}


int freeBST(Node* head)
{
	if(head != NULL)					// ������ȸ Ž���� �̿��Ͽ� �ڽ� ��带 ���� �޸� �����ϰ� �θ��带 �����Ѵ�.
	{
		freeBST(head->left);			
		if (head->right != head)		// ��Ʈ �������� Ž���Ѵ�.
		{
			freeBST(head->right);
		}
		free(head);						// �޸𸮸� ���� ���ش�.
	}
	
}





