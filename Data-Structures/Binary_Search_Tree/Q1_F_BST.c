
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
//BFS를 하는 것으로 보인다.
void levelOrderTraversal(BSTNode* root)
{
	QueueNode *headPtr = NULL;	//노드 자체를 초기화 안함
	QueueNode *tailPtr = NULL;	//노드 자체를 초기화 안함
	BSTNode * node = NULL;	//노드 자체를 초기화 안함

	enqueue(&headPtr, &tailPtr, root);
	// int arr[100];
	// int cnt = 0;

	while(headPtr != NULL)
	{
		node = dequeue(&headPtr, &tailPtr);
		// arr[cnt] = node->item;
		printf("%d ", node->item);
		if(node->left != NULL)	//NULL 값도 queue에 들어갈 수 있음
			enqueue(&headPtr, &tailPtr, node->left);
		if(node->right != NULL) //NULL 값도 queue에 들어갈 수 있음
			enqueue(&headPtr, &tailPtr, node->right);
			
		// cnt++;
	}

	// for(int i = 0; i < cnt+1; i++)
	// {
	// 	if(i == 0)
	// 		printf("%d", arr[i]);
		
	// 	else if(arr[i] != NULL)
	// 		printf(", %d", arr[i]);
	// }
	// printf(".");
	// free(arr);
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
{//queue 구조체를 따로 선언하지 않았기 때문에 head와 tail을 가리키는 포인터의 포인터를 매개변수로 받아 값을 수정
	// dynamically allocate memory
	QueueNode *newPtr = malloc(sizeof(QueueNode));
	//newPtr에 QueueNode의 사이즈만큼 동적으로 메모리를 할당한다.

	// if newPtr does not equal NULL
	if (newPtr != NULL) {		//newPtr이 NULL이 아니면
		newPtr->data = node;	//newPtr의 data는 node의 값이 대입된다.
		newPtr->nextPtr = NULL;	//newPtr의 다음 nextPtr에 NULL을 대입한다.
		// 
		// if queue is empty, insert at head
		if (isEmpty(*headPtr)) {//headPtr이 비었으면
			*headPtr = newPtr;	//headPtr에 newPtr을 대입한다. 
		}
		else { // insert at tail
			(*tailPtr)->nextPtr = newPtr;	//tailPtr의 nextPtr에 newPtr을 대입한다. newPtr이 꼬리가 된다.
		}

		*tailPtr = newPtr;					//tailPtr에 newPtr을 대입한다? 조건문에 else부분에 newPtr을 대입하는데 또?
		//여기서 tailPtr에 대입하는 것은 Queue의 tail을 newPtr로 한다는 뜻
	}
	else {
		printf("Node not inserted"); 
	}
}

BSTNode* dequeue(QueueNode **headPtr, QueueNode **tailPtr)
{//QueueNode를 가리키는 포인터의 포인터 headPtr, tailPtr을 받아서 BSTNode를 가리키는 포인터를 반환
	BSTNode *node = (*headPtr)->data; //BSTNode의 node에 headPtr의 data를 대입한다.
	//headPtr은 QueueNode *의 포인터 (QueueNode **)
	//*headPtr은 큐의 첫 번째 노드를 가리킴
	//(*headPtr)->data는 그 노드에 들어 있는 BSTNode 포인터
	//이걸 node라는 포인터 변수에 저장함
	QueueNode *tempPtr = *headPtr;	//QueueNode를 가리키는 포인터 temPtr에 headPtr의 값을 대입한다.
	//큐의 맨 앞 노드를 가리키는 포인터를 tempPtr에 복사(메모리 해제를 위해서 노드 저장)
	*headPtr = (*headPtr)->nextPtr; //headPtr에 headPtr의 nextPtr을 대입한다.
	//큐의 두 번째 노드가 새 head가 됨

	if (*headPtr == NULL) {			//headPtr이 NULL이면 
		//큐가 비었는지 확인, head와 tail을 NULL으로 바꾼다.
		*tailPtr = NULL;			//tailPtr을 NULL으로 한다.
	}

	free(tempPtr);					//tempPtr의 메모리 할당을 해제한다.
	//tempPtr에 저장해둔 큐의 맨 앞 노드의 메모리를 해제
	return node;					//저장해둔 노드의 데이터를 반환한다.
}

int isEmpty(QueueNode *head)		//QueueNode를 가리키는 포인터 head를 매개변수로 받는다.
{
	return head == NULL;			//head가 NULL이면 1을 반환
}

void removeAll(BSTNode **node)		//모든 노드를 삭제하는 함수, BSTNode를 가리키는 포인터의 포인터 node를 매개변수로 받는다.
{
	if (*node != NULL)				//node가 NULL이라면
	{
		removeAll(&((*node)->left));//재귀적으로 node 함수를 호출한다. 왼쪽 끝으로 이동
		removeAll(&((*node)->right));//재귀적으로 node 함수를 호출한다. 오른쪽 끝으로 이동
		free(*node);				//현재 노드의 메모리 할당을 해제한다.
		*node = NULL;				//해당 노드를 NULL으로 만든다.
	}
}
