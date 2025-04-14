//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section C - Stack and Queue Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode		//리스트 노드 구조체
{
	int item;
	struct _listnode *next;		//다음의 노드를 참조
} ListNode;	// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;					
	ListNode *head;		
} LinkedList;	// You should not change the definition of LinkedList


typedef struct _queue			//큐 자료구조
{
	LinkedList ll;
} Queue;  // You should not change the definition of Queue

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void createQueueFromLinkedList(LinkedList *ll, Queue *q); //큐 생성
void removeOddValues(Queue *q);	//나머지 값지우기?

void enqueue(Queue *q, int item);	//큐에 삽입
int dequeue(Queue *q);				//큐에서 디큐
int isEmptyQueue(Queue *q);			//큐가 비었는지
void removeAllItemsFromQueue(Queue *q); //큐에 모든 아이템을 삭제

void printList(LinkedList *ll);			//큐를 전부 프린트
ListNode * findNode(LinkedList *ll, int index);	//리스트에서 노드를 찾는 함수
int insertNode(LinkedList *ll, int index, int value);	//리스트에 노드를 삽입하는 함수
int removeNode(LinkedList *ll, int index);				//리스트에서 인덱스의 노드를 삭제하는 함수
void removeAllItems(LinkedList *ll);					//리스트의 모든 노드를 삭제하는 함수

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	int c, i;				
	LinkedList ll;
	Queue q;

	c = 1;

	// Initialize the linked list as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	// Initialize the Queue as an empty queue
	q.ll.head = NULL;
	q.ll.size = 0;


	printf("1: Insert an integer into the linked list:\n");
	printf("2: Create the queue from the linked list:\n");
	printf("3: Remove odd numbers from the queue:\n");
	printf("0: Quit:\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the List: ");	//LinkedList의 노드를 삽입
			scanf("%d", &i);
			insertNode(&ll, ll.size, i);//LinkedList의 노드를 삽입
			printf("The resulting linked list is: ");  
			printList(&ll);
			break;
		case 2:
			createQueueFromLinkedList(&ll, &q); // You need to code this function
			printf("The resulting queue is: ");
			printList(&(q.ll));		//q의 linkedList의 주소값을 매개변수로 함수를 호출한다.
			break;
		case 3:
			removeOddValues(&q); // You need to code this function
			printf("The resulting queue after removing odd integers is: ");
			printList(&(q.ll));
			removeAllItemsFromQueue(&q);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItemsFromQueue(&q);
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}


//////////////////////////////////////////////////////////////////////////////////

void createQueueFromLinkedList(LinkedList *ll, Queue *q)
{
	if(!isEmptyQueue(q))		//q가 비어있지 않으면
		removeAllItemsFromQueue(q);	//q의 모든 Item을 삭제한다.

	ListNode *cur;
	cur = ll->head;					//ll의 head노드부터 시작
	while(cur != NULL)				//cur이 NULL이 아니면 계속 반복
	{
		insertNode(&(q->ll), q->ll.size, cur->item);//q->ll에 맨 뒤 index에 현재 노드의 item을 삽입한다.
		cur = cur->next;							//다음 노드로 넘어간다.
	}
}

void removeOddValues(Queue *q)			//홀수 노드를 삭제하는 함수
{
	int Size = q->ll.size;			
	for(int i = 0; i < Size; i++)		//linkedlist의 노드 수만큼 반복
	{
		int cur = dequeue(q);			//cur에 item을 빼서
		if(cur % 2 == 0)				//item이 짝수면
			enqueue(q, cur);			//다시 q에 enqueue한다.
	}
}

//////////////////////////////////////////////////////////////////////////////////

void enqueue(Queue *q, int item) {			//q에 item을 enqueue 하는 함수
	insertNode(&(q->ll), q->ll.size, item);	//q->ll에 item을 삽입한다. q->ll.size인덱스에
}

int dequeue(Queue *q) {						//q에서 dequeue 하는 함수
	int item;								

	if (!isEmptyQueue(q)) {					//q가 비어있지 않다면
		item = ((q->ll).head)->item;		//item에 q의 linkedlist가 가리키는 head값의 item을 대입한다.
		removeNode(&(q->ll), 0);			//q의 linkedlist가 가리키는 주소값에 0번째 인덱스를 매개변수로 removeNode를 호출한다.
		return item;						//item값을 반환한다.
	}
	return -1;								//q가 비어있으면 -1을 반환한다.
}

int isEmptyQueue(Queue *q) {				//queue가 비어있는지 검사를 하는 함수
	if ((q->ll).size == 0)					//q의 ll의 size가 0이면, 여기서 q->ll->size로 접근이 안되는 이유가 뭘까? 
											//여기서 ll은 구조체이니까 .연산자를 쓰는 거고 q는 포인터이므로 ->으로 접근이 가능하다.
		return 1;							//1을 반환
	return 0;								//아니면 0을 반환
}

void removeAllItemsFromQueue(Queue *q)		//큐의 모든 아이템을 삭제하는 함수
{
	int count, i;					
	if (q == NULL)							//q가 NULL이면 return
		return;
	count = q->ll.size;						

	for (i = 0; i < count; i++)				//q의 size만큼 반복을 한다.
		dequeue(q);							//dequeue(q)를 호출한다.
}


void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;
	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode * findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		if (ll->head == NULL)
		{
			exit(0);
		}
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		if (pre->next == NULL)
		{
			exit(0);
		}
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;
		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
