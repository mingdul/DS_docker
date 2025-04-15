
//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024 //버퍼 사이즈?
///////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{ //트리의 노드
	int item;
	struct _bstnode *left; 	//왼쪽 자식을 가리키는 포인터
	struct _bstnode *right;	//오른쪽 자식을 가리키는 포인터
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _QueueNode {	//큐 노드
	BSTNode *data;			//BSTNode를 가리키는 포인터
	struct _QueueNode *nextPtr;	//다음 큐의 노드를 카리키는 포인터
}QueueNode; // You should not change the definition of QueueNode


typedef struct _queue	//큐
{
	QueueNode *head;		//큐의 head를 가리키는 포인터
	QueueNode *tail;		//큐의 tail을 가리키는 포인터
}Queue; // You should not change the definition of queue

///////////////////////////////////////////////////////////////////////////////////

// You should not change the prototypes of these functions
void levelOrderTraversal(BSTNode *node);

void insertBSTNode(BSTNode **node, int value);//BSTNode를 가리키는 포포인터
//value를 받아서 노드에 삽입하는 insertBSTNode 함수
BSTNode* dequeue(QueueNode **head, QueueNode **tail);//BSTNode를 가리키는 포인터를 반환하는 함수
//QueueNode 자료형을 가지는 포포인터, head, tail을 매개변수로 받는다.
void enqueue(QueueNode **head, QueueNode **tail, BSTNode *node);
//QueueNode 자료형을 가지는 포포인터, head, tail과 BSTNode를 가리키는 node라는 포인터를 매개변수로 받는다.
int isEmpty(QueueNode *head); 
//QueueNode를 가리키는 포인터 head를 매개변수로 가진다.
void removeAll(BSTNode **node);
//BSTNode를 가리키는 포포인터
///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	//Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode *root;	//BSTNode를 가리키는 포인터 root 선언
	root = NULL;	//root를 NULL으로 초기화

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the level-order traversal of the binary search tree;\n");
	printf("0: Quit;\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting level-order traversal of the binary search tree is: ");
			levelOrderTraversal(root); // You need to code this function
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
//너비 우선 탐색을 하는 것으로 보인다.
void levelOrderTraversal(BSTNode* root)
{

    /* add your code here */
}

///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value){	//BSTNode의 포포인터
	if (*node == NULL)	//node라는 BSTNode의 포인터가 NULL이라면
	{
		*node = malloc(sizeof(BSTNode));//동적 메모리 할당

		if (*node != NULL) {//BSTNode를 가리키는 포인터가 NULL이라면			
			(*node)->item = value;	//node의 item을 value로 초기화한다.
			(*node)->left = NULL;	//왼쪽 자식노드를 NULL으로 초기화
			(*node)->right = NULL;	//오른쪽 자식노드를 NULL으로 초기화
		}
	}
	else
	{
		if (value < (*node)->item)	//값이 현재 부모노드의 값보다 작다면
		{	
			insertBSTNode(&((*node)->left), value);	//재귀적으로 왼쪽으로 내려간다.
		}
		else if (value >(*node)->item)	//값이 현재 부모노드의 값보다 크다면
		{
			insertBSTNode(&((*node)->right), value);//제귀적으로 오른쪽 으로 내려간다.
		}
		else	// 값이 같다면 return?
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

// enqueue node
void enqueue(QueueNode **headPtr, QueueNode **tailPtr, BSTNode *node)
{
	// dynamically allocate memory
	QueueNode *newPtr = malloc(sizeof(QueueNode));
	//newPtr에 QueueNode의 사이즈만큼 동적으로 메모리를 할당한다.

	// if newPtr does not equal NULL
	if (newPtr != NULL) {		//newPtr이 NULL이 아니면
		newPtr->data = node;	//newPtr의 data는 node의 값이 대입된다.
		newPtr->nextPtr = NULL;	//newPtr의 다음 nextPtr에 NULL을 대입한다.
		// 
		// if queue is empty, insert at head
		if (isEmpty(*headPtr)) {
			*headPtr = newPtr;
		}
		else { // insert at tail
			(*tailPtr)->nextPtr = newPtr;
		}

		*tailPtr = newPtr;
	}
	else {
		printf("Node not inserted");
	}
}

BSTNode* dequeue(QueueNode **headPtr, QueueNode **tailPtr)
{
	BSTNode *node = (*headPtr)->data;
	QueueNode *tempPtr = *headPtr;
	*headPtr = (*headPtr)->nextPtr;

	if (*headPtr == NULL) {
		*tailPtr = NULL;
	}

	free(tempPtr);

	return node;
}

int isEmpty(QueueNode *head)
{
	return head == NULL;
}

void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}
